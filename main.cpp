#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;

int main()
{
    //The main window
    RenderWindow app(VideoMode(520, 450), "Arkanoid");
    app.setFramerateLimit(60);

    //Variables for moving paddle
    int xAxis=400;
    bool lPressed=false;
    bool rPressed=false;

    int count=0;

    //loading images
    Texture t1,t2,t3,t4,t5,t6,t7,t8,win,lose;
    t1.loadFromFile("images/block03.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/paddle.png");
    t5.loadFromFile("images/block01.png");
    t6.loadFromFile("images/block02.png");
    t7.loadFromFile("images/block04.png");
    t8.loadFromFile("images/block05.png");
    win.loadFromFile("images/win.jpg");
    lose.loadFromFile("images/image.jpg");

    RectangleShape sBackground;
    Sprite sBall(t3);
    sBackground.setTexture(&t2);
    sBackground.setSize(sf::Vector2f(520,450));

    //pause image
     RectangleShape pauseImage;
     pauseImage.setSize(sf::Vector2f(520,450));

    //paddle
    RectangleShape sPaddle;
    sPaddle.setTexture(&t4);
    sPaddle.setSize(sf::Vector2f(200,20));

     // Load the sounds used in the game
  sf::SoundBuffer ballSoundBuffer;
  sf::Sound ballSound(ballSoundBuffer);

    //multiple blocks
    Sprite block[1000];
    int n=0;
    for (int i=1;i<=10;i++)
    for (int j=1;j<=10;j++)
      {
         if(j%2==0&&i%2==0){block[n].setTexture(t1);}
         else if(j%3==0){block[n].setTexture(t5);}
         else if(i%4==0){block[n].setTexture(t8);}
         else if(i%5==0){block[n].setTexture(t7);}
         else if(j%2==0){block[n].setTexture(t6);}
         else{
    block[n].setTexture(t8);
         }
         block[n].setPosition(i*43,j*20);
         n++;
      }

    //collision values
    float dx=6, dy=5;

    //position of ball
    float x=300, y=300;

    while (app.isOpen())
    {
         //check win/lose
    bool playing=true;
       Event e;
       while (app.pollEvent(e))
       {
         if (e.type == Event::Closed)
             app.close();

                      //Left
                      if(e.type == sf::Event::KeyPressed && (e.key.code ==sf::Keyboard::Left ))

                        {
                            lPressed =true;
                        }


                      //Right
                      if(e.type == sf::Event::KeyPressed && (e.key.code == sf::Keyboard::Right))

                        {
                            rPressed =true;
                        }
       }
       if (lPressed == true)
                        {

                            xAxis<=0?xAxis:xAxis-=50;
                            lPressed = false;
                        }
                        if (rPressed == true)
                        {

                            xAxis<=420?xAxis+=50:xAxis;
                            rPressed = false;
                        }

                     sPaddle.setPosition(250,400);

    x+=dx;
    for (int i=0;i<n;i++){
        if ( sBall.getGlobalBounds().intersects(block[i].getGlobalBounds()) )
             {

                 block[i].setPosition(-100,0); dx=-dx;

             count++;}
    }


    y+=dy;
    for (int i=0;i<n;i++){
        if ( sBall.getGlobalBounds().intersects(block[i].getGlobalBounds()) )
             {

                 block[i].setPosition(-100,0); dy=-dy;
             count++;
             }
            }
            if(count==n) {
                playing=false;
                pauseImage.setTexture(&win);

            }

    if (x<0 || x>520)  dx=-dx;
    if (y<0)  dy=-dy;
    if(y>=445){
        playing=false;
       pauseImage.setTexture(&lose);

    }
    else if( sBall.getGlobalBounds().intersects(sPaddle.getGlobalBounds()) ){
            ballSoundBuffer.loadFromFile("Data/ball.wav");
             ballSound.play();
            dy=-(rand()%5+2);

    }

sBall.setPosition(x,y);

    app.clear();
    if(playing==true){

        app.draw(sBackground);
        app.draw(sBall);
        app.draw(sPaddle);

       for (int i=0;i<n;i++)
          app.draw(block[i]);
    }
    else{
        app.draw(sBackground);
        app.draw(pauseImage);

    }

     app.display();

    }
  return 0;
}
