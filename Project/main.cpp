#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include<math.h>
#include<fstream>



using namespace std;
void window_color(SDL_Renderer *Renderer, int R, int G, int B);
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian );
void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian);
void my_line(SDL_Renderer *Renderer, int x_1, int y_1, int L,double theta,int widht, int R, int G, int B );
void texture(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height);
int jump(double y, double t);
double move_yball(double t,int v,double y);
void goal_cel(SDL_Renderer *m_renderer,double x,char c1,char c2);
bool spacetest (string s1,string s2);

int stringtoint(string n);
void inttostring (string &s , int a);
void reverseStr(string& str);
void addnumber (string &s , int a);

int volume=64;

int main( int argc, char * argv[] )
{

while(1){

        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
        Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
        Mix_Music *background = Mix_LoadMUS("game.mp3");
        Mix_Music *menu_s = Mix_LoadMUS("menu.mp3");
        Mix_Chunk *ball = Mix_LoadWAV("ball.wav");
        Mix_Chunk *crowd = Mix_LoadWAV("crowd.wav");
        Mix_Chunk *whistle = Mix_LoadWAV("whistle.wav");
        Mix_Chunk *click = Mix_LoadWAV("click.wav");
        Mix_Chunk *power = Mix_LoadWAV("power.wav");



int W = 700;//ertefa safhe
    int L = 1120;//tool safhe
      // be ina kari nadashte bashid
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;//| SDL_WINDOW_FULLSCREEN_DESKTOP;//SDL_WINDOW_BORDERLESS ;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( L, W, WND_flags, &m_window, &m_renderer );
    //Pass the focus to the drawing window
    SDL_RaiseWindow(m_window);
    //Get screen res olution
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    // be ina kari nadashte bashid


  int RNX = 200, RNY = 200;
SDL_Event *event = new SDL_Event();


    int l;
    string s[901];
    ifstream mylist;

    mylist.open("names.txt");
    mylist>>s[0];

    l=stringtoint(s[0]);

    for(int i=1 ; i<=9*l ; i++)
        mylist>>s[i];

    mylist.close();



    bool getname1=false,getname2=false,game=false,ch_skin=false,finish=false,menu=true , setting=false , league= false,pause=false;

    Mix_PlayMusic(menu_s,-1);

    SDL_Event *e = new SDL_Event();
    SDL_Event *m = new SDL_Event();
    int mousex,mousey;

    //menu
     while (menu)
    {
        texture(m_renderer,0,0,"main.jpg",1120,700);

        texture(m_renderer,460,150,"play.png",200,100);
        texture(m_renderer,460,300,"setting.png",200,100);
        texture(m_renderer,460,450,"League.png",200,100);
        texture(m_renderer,900,600,"CR.png",200,70);


        SDL_PollEvent(e);

        if ( e->type == SDL_MOUSEBUTTONDOWN )
            {
                SDL_GetMouseState(&mousex , &mousey) ;

           if (mousey>150 && mousey < 250 && mousex > 460 && mousex < 660)
                {Mix_PlayChannel(-1,click,0);  getname1=true;     menu=false;}

            if (mousey>300 && mousey < 400 && mousex > 460 && mousex < 660)
                {Mix_PlayChannel(-1,click,0);  setting=true;}

            if (mousey>450 && mousey < 550 && mousex > 460 && mousex < 660)
                {Mix_PlayChannel(-1,click,0);  league=true;}


        while(setting)
        {
           texture(m_renderer,0,0,"main.jpg",1120,700);
           texture(m_renderer,50,50,"back.png",200,100);
           texture(m_renderer,460,150,"sound.png",200,100);
           texture(m_renderer,180,350,"guide.png",770,350);
           rect(m_renderer,300,300,512,15,190,190,190,1);
           rect(m_renderer,300+4*volume,290,20,40,160,160,100,1);

           if( SDL_PollEvent( m ))
            {
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_RIGHT]) {if(volume<128) volume+=8;}
            if (state[SDL_SCANCODE_LEFT]) {if(volume>0) volume-=8;}

        if ( m->type == SDL_MOUSEBUTTONDOWN )
            {
                SDL_GetMouseState(&mousex , &mousey) ;
                 if (mousey>50 && mousey < 150 && mousex > 50 && mousex < 250)
                    {Mix_PlayChannel(-1,click,0);  setting=false;}
            }}
        Mix_VolumeMusic(volume);
        Mix_VolumeChunk(ball,volume);
        Mix_VolumeChunk(crowd,volume);
        Mix_VolumeChunk(whistle,volume);
        Mix_VolumeChunk(click,volume);


           SDL_RenderPresent( m_renderer );
           SDL_Delay(20);
           SDL_RenderClear(m_renderer);
        }

    window_color(m_renderer,0,0,0);

        int topfive[4];
    if(league)
    {

    int maxx;
    maxx = -100 ;

    for(int i=0 ; i<l ; i++)
        if(  stringtoint ( s[9*i+2] ) > maxx)
        {
            maxx = stringtoint ( s[9*i+2] ) ;
            topfive[0]=i;
        }


   maxx = -100;
    for(int i=0;i<l;i++)
         {
             if(stringtoint ( s[9*i+2] ) > maxx )
                if(topfive[0]!=i)
                {
                    maxx=stringtoint ( s[9*i+2] );
                    topfive[1]=i;
                }
         }

   maxx = -100;
    for(int i=0;i<l;i++)
           {
               if(stringtoint ( s[9*i+2] )>maxx )
                    if(topfive[0]!=i)
                        if(topfive[1]!=i)
                        {
                            maxx=stringtoint ( s[9*i+2] );
                            topfive[2]=i;
                        }

           }


   maxx = -100;
    for(int i=0;i<l;i++)
        {
            if(stringtoint ( s[9*i+2] )>maxx)
                    if(topfive[0]!=i)
                        if(topfive[1]!=i)
                            if(topfive[2]!=i)
                            {
                                maxx=stringtoint ( s[9*i+2] );
                                topfive[3]=i;
                            }

        }


    maxx = -100;
    for(int i=0;i<l;i++)
         {
            if(stringtoint ( s[9*i+2] )>maxx)
                    if(topfive[0]!=i)
                        if(topfive[1]!=i)
                            if(topfive[2]!=i)
                                if(topfive[3]!=i)
                                {
                                    maxx=stringtoint ( s[9*i+2] );
                                    topfive[4]=i;
                                }

         }
    }




        while(league)
        {
           texture(m_renderer,0,0,"main.jpg",1120,700);
           texture(m_renderer,50,50,"back.png",200,100);
           rect(m_renderer,35,180,1060,60,0,0,0,1);
           rect(m_renderer,35,240,1060,60,100,100,100,1);
           rect(m_renderer,35,300,1060,60,70,70,70,1);
           rect(m_renderer,35,360,1060,60,100,100,100,1);
           rect(m_renderer,35,420,1060,60,70,70,70,1);
           rect(m_renderer,35,480,1060,60,100,100,100,1);

           int y=200,R=250,G=250,B=250,A=250;
    textRGBA(m_renderer,50,y,"names" ,2,24,R,G,B,A);
    textRGBA(m_renderer,240,y,"score" ,2,24,R,G,B,A);
    textRGBA(m_renderer,340,y ,"win" ,2,24,R,G,B,A);
    textRGBA(m_renderer,440,y ,"Equal" ,2,24,R,G,B,A);
    textRGBA(m_renderer,540,y ,"lose" ,2,24,R,G,B,A);
    textRGBA(m_renderer,640,y ,"goal-for" ,2,24,R,G,B,A);
    textRGBA(m_renderer,740,y ,"goal-against" ,2,24,R,G,B,A);
    textRGBA(m_renderer,940,y,"games played" ,2,24,R,G,B,A);



    for(int j=0;j<l && j<5 ;j++)
        textRGBA(m_renderer, 60 , 250+60*j , s[9*topfive[j]+1].c_str() ,2,24,R,G,B,A);



    for(int i=2 ; i<=9 ; i++)
        for(int j=0;j<l && j<5 ;j++)
            if(i!=8)
            textRGBA(m_renderer, 60+100*i , 250+60*j , s[9*topfive[j]+i].c_str() ,2,24,R,G,B,A);

           SDL_PollEvent(m);

        if ( m->type == SDL_MOUSEBUTTONDOWN )
            {
                SDL_GetMouseState(&mousex , &mousey) ;
                 if (mousey>50 && mousey < 150 && mousex > 50 && mousex < 250)
                    {Mix_PlayChannel(-1,click,0);  league=false;}
            }

           SDL_RenderPresent( m_renderer );
           SDL_Delay(20);
           SDL_RenderClear(m_renderer);
        }
}


        SDL_RenderPresent( m_renderer );
        SDL_Delay(20);
        SDL_RenderClear(m_renderer);
    }
    //menu




            SDL_StartTextInput();
            int time=0;
            string player1 = " ",  player2 = " ";
            int pl1=-1,pl2=-1;


            //getting name
            {

            while(getname1)
            {
                texture(m_renderer,0,0,"main.jpg",1120,700);
                textRGBA(m_renderer, 100 , 150 , "player1", 2 , 40 , 255,255,255,255);
                rect(m_renderer,250,145,500,50,0,0,0,1);
                textRGBA(m_renderer, 300 , 200 , "Press tab to continue", 2 , 40 , 180,180,100,255);

                SDL_PollEvent(e);
                if (e->key.keysym.sym == SDLK_TAB )
                    {Mix_PlayChannel(-1,click,0);  getname1=false; getname2=true; break;}

            if (time %10 == 0)
                {
                    time=1;

                    if( player1 [player1.length() - 1] == '|' )
                        player1.erase(player1.size()-1);

                    else
                        player1 += "|" ;
                }


            if(e->key.keysym.sym == SDLK_BACKSPACE && e->type== SDL_KEYDOWN && player1.length() > 0)
            {

                if(player1[player1.length() -1] == '|')
                {
                    player1.erase(player1.size()-1);
                    player1.erase(player1.size()-1);
                    player1 += '|' ;
                }

                else

                {
                    player1.erase(player1.size()-1);
                }
                e->type == NULL ;
            }

        if ( e->type == SDL_TEXTINPUT)
        {
            if(player1[player1.length() -1] == '|')
            {
                 player1.erase(player1.size()-1);
                 player1 += e->text.text;
                 player1 += '|';
            }
            else
                player1 += e->text.text;
        }

        textRGBA(m_renderer, 250 , 150 , player1.c_str(), 1 , 40 , 255,255,255,255);
        SDL_RenderPresent(m_renderer);
        SDL_Delay(50);
        SDL_RenderClear(m_renderer);
        time++;

        if(player1[player1.length() -1] == '|')
            player1.erase(player1.size()-1);

        SDL_StartTextInput();
        e->type =0;

    }

    while(getname2)
            {
                texture(m_renderer,0,0,"main.jpg",1120,700);
                textRGBA(m_renderer, 100 , 300 , "player2", 2 , 40 , 255,255,255,255);
                rect(m_renderer,250,295,500,50,0,0,0,1);
                textRGBA(m_renderer, 300 , 350 , "Press enter to continue", 2 , 40 , 180,180,100,255);

                SDL_PollEvent(e);
                if (e->key.keysym.sym == SDLK_RETURN )
                    {Mix_PlayChannel(-1,click,0);  getname2=false; ch_skin=true; break;}

            if (time %10 == 0)
                {
                    time=1;

                    if( player2 [player2.length() - 1] == '|' )
                        player2.erase(player2.size()-1);

                    else
                        player2 += "|" ;
                }


            if(e->key.keysym.sym == SDLK_BACKSPACE && e->type== SDL_KEYDOWN && player2.length() > 0)
            {

                if(player2[player2.length() -1] == '|')
                {
                    player2.erase(player2.size()-1);
                    player2.erase(player2.size()-1);
                    player2 += '|' ;
                }

                else

                {
                    player2.erase(player2.size()-1);
                }
                e->type == NULL ;
            }

        if ( e->type == SDL_TEXTINPUT)
        {
            if(player2[player2.length() -1] == '|')
            {
                 player2.erase(player2.size()-1);
                 player2 += e->text.text;
                 player2 += '|';
            }
            else
                player2 += e->text.text;
        }

        textRGBA(m_renderer, 250 , 300 , player2.c_str(), 1 , 40 , 255,255,255,255);
        SDL_RenderPresent(m_renderer);
        SDL_Delay(50);
        SDL_RenderClear(m_renderer);
        time++;

        if(player2[player2.length() -1] == '|')
            player2.erase(player2.size()-1);

        SDL_StartTextInput();
        e->type =0;



    }

    string str;
    for(int i=0;i<l;i++)
    {
        if(spacetest(s[9*i+1],player1))
            {pl1=i; break;}
    }
    for(int i=0;i<l;i++)
    {
        if(spacetest(s[9*i+1],player2))
            {pl2=i; break;}
    }


   if(pl1==-1)
    {
        s[9*l+1]=player1;
        for(int i=2;i<=9;i++)
            s[9*l+i]= '0' ;


        pl1=l;
        l++;
    }


   if(pl2==-1)
    {
        s[9*l+1]=player2;
        for(int i=2;i<=9;i++)
            s[9*l+i]='0';


        pl2=l;
        l++;
    }

   inttostring(str,l);
    s[0]=str;
}
           // getting name




        char char1='q',char2='q';

            //choosing skin
            while(ch_skin){

            texture(m_renderer,0,0,"main.jpg",1120,700);
            texture(m_renderer,150,150,"cat1_e.png",200,200);
            texture(m_renderer,360,150,"cat1_r.png",200,200);
            texture(m_renderer,570,150,"cat1_t.png",200,200);
            texture(m_renderer,780,150,"cat1_y.png",200,200);
            texture(m_renderer,150,400,"cat2_u.png",200,200);
            texture(m_renderer,360,400,"cat2_i.png",200,200);
            texture(m_renderer,780,400,"cat2_p.png",200,200);
            texture(m_renderer,570,400,"cat2_o.png",200,200);

            textRGBA(m_renderer, 100 , 100 , "player1", 2 , 40 , 255,255,255,255);
            textRGBA(m_renderer, 100 , 350 , "player2", 2 , 40 , 255,255,255,255);
            textRGBA(m_renderer, 300 , 50 , "Press enter to start Game", 2 , 40 , 180,180,100,255);
            textRGBA(m_renderer, 600 , 610 , "Press u,i,o,p for player2", 2 , 30 , 180,180,100,255);
            textRGBA(m_renderer, 250 , 610 , "Press e,r,t,y for player1", 2 , 30 , 180,180,100,255);

            if(char1=='e'){rect(m_renderer,150,150,200,200,250,250,250,0);}
            if(char1=='r'){rect(m_renderer,360,150,200,200,250,250,250,0);}
            if(char1=='t'){rect(m_renderer,570,150,200,200,250,250,250,0);}
            if(char1=='y'){rect(m_renderer,780,150,200,200,250,250,250,0);}
            if(char2=='u'){rect(m_renderer,150,400,200,200,250,250,250,0);}
            if(char2=='i'){rect(m_renderer,360,400,200,200,250,250,250,0);}
            if(char2=='o'){rect(m_renderer,570,400,200,200,250,250,250,0);}
            if(char2=='p'){rect(m_renderer,780,400,200,200,250,250,250,0);}


                if( SDL_PollEvent( event ))
            {
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_E]){Mix_PlayChannel(-1,click,0);  char1='e';}
            if (state[SDL_SCANCODE_R]){Mix_PlayChannel(-1,click,0);  char1='r';}
            if (state[SDL_SCANCODE_T]){Mix_PlayChannel(-1,click,0);  char1='t';}
            if (state[SDL_SCANCODE_Y]){Mix_PlayChannel(-1,click,0);  char1='y';}
            if (state[SDL_SCANCODE_U]){Mix_PlayChannel(-1,click,0);  char2='u';}
            if (state[SDL_SCANCODE_I]){Mix_PlayChannel(-1,click,0);  char2='i';}
            if (state[SDL_SCANCODE_O]){Mix_PlayChannel(-1,click,0);  char2='o';}
            if (state[SDL_SCANCODE_P]){Mix_PlayChannel(-1,click,0);  char2='p';}
            if (state[SDL_SCANCODE_RETURN] && char1!='q' && char2!='q'){Mix_PlayChannel(-1,click,0);  ch_skin=false; game=true; break;}
            }
            SDL_RenderPresent(m_renderer);
            SDL_Delay(20);
            SDL_RenderClear(m_renderer);
            }
            //choosing skin

            Mix_FreeMusic(menu_s);
            Mix_PlayChannel(-1,crowd,0);

            for(int e=1;e<=15;e++)
                {string Pic="enter",I;
                stringstream P;
                P<<e;
                P>>I;
                Pic+=I;
                Pic+=".jpg";
                texture(m_renderer,0,0,Pic,1120,700);
                SDL_RenderPresent(m_renderer);
                SDL_Delay(100);
                SDL_RenderClear(m_renderer);}


            Mix_PlayMusic(background,-1);

                double x_ball=535, y_ball=30, dx_b=10, dy_b=10, y0_b=510;
                int x_cat1=200, x_cat2=820, y_cat1=480, y_cat2=480;
                unsigned long long int kick_t1=0,kick_t2=0,time_jump1=0,time_jump2=0;
                char h='1',j='1',inv=' ',sta='1';
                bool jump1=false, jump2=false;
                bool ball_kick1=false, ball_kick2=false, ball_kick3=false;
                double t=0;
                int v=19;
                int fire=1,r=25;
                bool outside=false,goal=false,start=true,first_start=true;

                unsigned long long int start_time=SDL_GetTicks(),pause_time=0;
                string time_game;
                stringstream T;

                unsigned long long int pow_line1=SDL_GetTicks()+20000,pow_line2=SDL_GetTicks()+20000;
                int pow1,pow2;

                bool invisibleball=false,kickfireball=false,punch1=false,punch2=false,tripleclone1=false,tripleclone2=false,star1=false,star2=false;
                unsigned long long int invisible=0,punching1=0,punching2=0,triple1=0,triple2=0,star_t1=0,star_t2=0;
                int y1_triple=0,y2_triple=0,x1_triple=0,x2_triple=0;
                int Q1=-1,Q2=-1;

                string goal1="0",goal2="0";
                int g1=0,g2=0;
                stringstream G;

                string player1_skin="cat1_", player2_skin="cat2_";
                player1_skin.push_back(char1); player2_skin.push_back(char2);
                player1_skin+=".png"; player2_skin+=".png";



            //Game
          while(game){


            if(start){if(y_ball<510) y_ball+=10; else{y_ball=510; start=false; first_start=false;}}

            if(kick_t1<SDL_GetTicks()) h='1';
            if(kick_t2<SDL_GetTicks()) j='1';



            string tail1="tail1_", tail2="tail2_";
            tail1.push_back(char1); tail2.push_back(char2);
            tail1.push_back(h); tail2.push_back(j);
            tail1+=".png"; tail2+=".png";

            string B="ball.png";
            B.push_back(inv);

            texture(m_renderer,0,0,"background.jpg",1120,703);

            rect(m_renderer,20,50,440,50,0,0,0,1);
            rect(m_renderer,660,50,440,50,0,0,0,1);
            textRGBA(m_renderer, 90 , 50 , player1.c_str(), 2 , 40 , 255,255,255,255);
            textRGBA(m_renderer, 730 , 50 , player2.c_str(), 2 , 40 , 255,255,255,255);
            texture(m_renderer,20,50,player1_skin,50,50);
            texture(m_renderer,1050,50,player2_skin,50,50);
            textRGBA(m_renderer,420,50,goal1.c_str(),2,40,255,255,255,255);
            textRGBA(m_renderer,670,50,goal2.c_str(),2,40,255,255,255,255);

            texture(m_renderer,x_cat1+70,y_cat1+30,tail1,60,60);
            texture(m_renderer,x_cat2-40,y_cat2+30,tail2,60,60);
            texture(m_renderer,x_cat1,y_cat1,player1_skin,90,90);
            texture(m_renderer,x_cat2,y_cat2,player2_skin,90,90);


            texture(m_renderer,x_ball,y_ball,B,50,50);

            if(y_ball<190 && start && first_start) {texture(m_renderer,470,200,"1.png",130,200); if(y_ball<80) Mix_PlayChannel(-1,whistle,0);}
            if(y_ball>190 && y_ball<390 && start && first_start) {texture(m_renderer,470,200,"2.png",130,200); if(y_ball<230) Mix_PlayChannel(-1,whistle,0);}
            if(y_ball>390 && y_ball<510 && start && first_start) {texture(m_renderer,470,200,"3.png",130,200); if(y_ball<430) Mix_PlayChannel(-1,whistle,0);}

            if(jump1){y_cat1=jump(y_cat1,SDL_GetTicks()-time_jump1); if(y_cat1>=480) {jump1=false; time_jump1=0; y_cat1=480;}}
            if(jump2){y_cat2=jump(y_cat2,SDL_GetTicks()-time_jump2); if(y_cat2>=480) {jump2=false; time_jump2=0; y_cat2=480;}}

            if((x_ball<190 && y_ball<390)||(x_ball+50>910 && y_ball<390)){if(x_ball<190) {x_ball=190; dx_b=abs(dx_b);} if(x_ball>860) {x_ball=860; dx_b=-abs(dx_b);}}
            if((x_ball<160 && y_ball>390)||(x_ball>900 && y_ball>390)){ dx_b=0;   if(y_ball==510){Mix_PlayChannel(-1,crowd,0); ball_kick1=false; ball_kick2=false; ball_kick3=false; start=true;
                                                                                                                            if(x_ball>800){g1++; G<<g1; goal1=G.str(); G.str(" ");}
                                                                                                                            if(x_ball<200){g2++; G<<g2; goal2=G.str(); G.str(" ");}
                                                                                                                              x_cat1=200; y_cat1=480; x_cat2=820; y_cat2=480; y_ball=30; x_ball=535;
                                                                                                                              kickfireball=false; tripleclone1=false; tripleclone2=false; y1_triple=0; y2_triple=0; x1_triple=0; x2_triple=0;
                                                                                                                              goal_cel(m_renderer,x_ball,char1,char2);}}


            if(ball_kick2){ y_ball=move_yball(t,v,y0_b);
                            x_ball+=dx_b;
                            t+=1.5;
                            if(y_ball>510){t=0; v-=3; y_ball=510; y0_b=510; if(v<16)kickfireball=false; if(v<3) {ball_kick2=false;} Mix_PlayChannel(-1,ball,0);}
                            if(x_ball<130 || x_ball>930){dx_b*=-1;}}
            if(ball_kick1){ y_ball=move_yball(t,v,y0_b);
                            x_ball+=dx_b;
                            t+=1;
                            if(y_ball>510){t=0; v-=3; y_ball=510; y0_b=510; if(v<10)kickfireball=false; if(v<3) {ball_kick1=false;} Mix_PlayChannel(-1,ball,0);}
                            if(x_ball<130 || x_ball>930){dx_b*=-1;}}
            if(ball_kick3){ y_ball=move_yball(t,v,y0_b);
                            x_ball+=dx_b;
                            t+=1;
                            if(y_ball>510){t=0; v-=3; y_ball=510; y0_b=510; if(v<10)kickfireball=false; if(v<3) {ball_kick3=false;} Mix_PlayChannel(-1,ball,0);}
                            if(x_ball<130 || x_ball>930){dx_b*=-1;}}

            if(x_ball+50>x_cat1+10 && x_ball<x_cat1+80 && y_ball+50>y_cat1+10 && y_ball<y_cat1+20){if(kickfireball && y_ball!=510){if(x_cat1-200>70) x_cat1-=200; else x_cat1=70; star1=true; star_t1=SDL_GetTicks()+3000; kickfireball=false;} y_ball=y_cat1-40; y0_b=y_ball; t=0; v-=3;}
            if(x_ball+50>x_cat1+x1_triple+10 && x_ball+50<x_cat1+45 && y_ball>y_cat1+y1_triple+10 && y_ball<y_cat1+80){dx_b*=-1; x_ball=x_cat1+x1_triple-40;}
            if(x_ball>x_cat1+45 && x_ball<x_cat1+80 && y_ball>y_cat1+y1_triple+10 && y_ball<y_cat1+80){if(kickfireball && y_ball!=510){if(x_cat1-200>70) x_cat1-=200; else x_cat1=70; star1=true; star_t1=SDL_GetTicks()+3000; kickfireball=false;}  dx_b*=-1; x_ball=x_cat1+80;}

            if(x_ball+50>x_cat2+10 && x_ball<x_cat2+80 && y_ball+50>y_cat2+10 && y_ball<y_cat2+20){if(kickfireball && y_ball!=510){if(x_cat2+200<945) x_cat2+=200; else x_cat2=945; star2=true; star_t2=SDL_GetTicks()+3000; kickfireball=false;} y_ball=y_cat2-40; y0_b=y_ball; t=0; v-=3;}
            if(x_ball+50>x_cat2+10 && x_ball+50<x_cat2+45 && y_ball>y_cat2+y2_triple+10 && y_ball<y_cat2+80){if(kickfireball && y_ball!=510){if(x_cat2+200<945) x_cat2+=200; else x_cat2=945; star2=true; star_t2=SDL_GetTicks()+3000; kickfireball=false;}   dx_b*=-1; x_ball=x_cat2-40;}
            if(x_ball>x_cat2+45 && x_ball<x_cat2+x2_triple+80 && y_ball>y_cat2+y2_triple+10 && y_ball<y_cat2+80){dx_b*=-1; x_ball=x_cat2+x2_triple+80;}



            T<<((SDL_GetTicks()-start_time)/1000);  time_game=T.str(); textRGBA(m_renderer,525,40,time_game.c_str(),2,60,255,0,0,255); T.str(" ");
            rect(m_renderer,20,110,200,20,200,200,200,1);
            rect(m_renderer,900,110,200,20,200,200,200,1);
            if(pow_line1<=SDL_GetTicks()) pow1=200;  else pow1=200-(pow_line1-SDL_GetTicks())/100;
            if(pow_line2<=SDL_GetTicks()) pow2=200;  else pow2=200-(pow_line2-SDL_GetTicks())/100;
            rect(m_renderer,20,110,pow1,20,200,50,50,1);
            rect(m_renderer,900,110,pow2,20,200,50,50,1);
            if(SDL_GetTicks()-start_time>=90000 || g1==5 || g2==5 || (g1==4 && g2==4)) {Mix_PlayChannel(-1,whistle,0); Mix_PlayChannel(-1,crowd,0); ball_kick1=false; ball_kick2=false; ball_kick3=false; game=false; finish=true;}


            if(Q1>-1){switch(Q1){case 0:{invisibleball=true; invisible=SDL_GetTicks()+3000; Q1=-1; break;}
                                 case 1:{kickfireball=true; Q1=-1; break;}
                                 case 2:{punch2=true; punching2=SDL_GetTicks()+700; Q1=-1; break;}
                                 case 3:{tripleclone1=true; triple1=SDL_GetTicks()+8000; y1_triple=-60; x1_triple=-70; Q1=-1; break;}
                                }}
            if(Q2>-1){switch(Q2){case 0:{invisibleball=true; invisible=SDL_GetTicks()+3000; Q2=-1; break;}
                                 case 1:{kickfireball=true; Q2=-1; break;}
                                 case 2:{punch1=true; punching1=SDL_GetTicks()+700; Q2=-1; break;}
                                 case 3:{tripleclone2=true; triple2=SDL_GetTicks()+8000; y2_triple=-60; x2_triple=70; Q2=-1; break;}
                                }}


            if(invisibleball) {if(invisible>SDL_GetTicks()) inv='Q'; else {invisibleball=false; inv=' ';}}
            if(kickfireball) if(ball_kick1 || ball_kick2 || ball_kick3){if(fire<10){ for(int F=fire;F>1;F--)  filledEllipseRGBA(m_renderer,x_ball+25-F*dx_b,y_ball+25-F*dy_b,r*(10-F)/10,r*(10-F)/10,255,55,55,200); fire++;}
                                                                        else fire=1;}
            if(tripleclone1) {if(triple1>SDL_GetTicks())  {texture(m_renderer,x_cat1-80,y_cat1,player1_skin,90,90); texture(m_renderer,x_cat1-40,y_cat1-50,player1_skin,90,90);}
                            else {tripleclone1=false; y1_triple=0; x1_triple=0;}}

            if(tripleclone2) {if(triple2>SDL_GetTicks())  {texture(m_renderer,x_cat2+80,y_cat2,player2_skin,90,90); texture(m_renderer,x_cat2+40,y_cat2-50,player2_skin,90,90);}
                            else {tripleclone2=false; y2_triple=0; x2_triple=0;}}

            if(punch1) if(punching1>SDL_GetTicks()) {texture(m_renderer,x_cat1+20,y_cat1-30,"punch.png",60,60);}
                    else {star1=true; star_t1=SDL_GetTicks()+3000; punch1=false;}
            if(punch2) if(punching2>SDL_GetTicks()) {texture(m_renderer,x_cat2+20,y_cat2-30,"punch.png",60,60);}
                    else {star2=true; star_t2=SDL_GetTicks()+3000; punch2=false;}

            string S="star";  S.push_back(sta); S+=".png";
            if(star1) if(star_t1>SDL_GetTicks()){texture(m_renderer,x_cat1+10,y_cat1-30,S,70,50);}
                        else star1=false;

            if(star2) if(star_t2>SDL_GetTicks()){texture(m_renderer,x_cat2+10,y_cat2-30,S,70,50);}
                        else star2=false;

            if(star1 || star2) {if(sta=='1') sta='2'; else sta='1';}




            texture(m_renderer,115,370,"gate1.png",90,220);
            texture(m_renderer,910,370,"gate2.png",90,220);

            SDL_RenderPresent(m_renderer);
            SDL_Delay(20);
            SDL_RenderClear(m_renderer);



            if( SDL_PollEvent( event ) && start==false )
            {
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(star1==false)
            {if (state[SDL_SCANCODE_A]) if(x_cat1>150) x_cat1-=10;
            if (state[SDL_SCANCODE_D]) if(x_cat1<x_cat2-160) x_cat1+=10;
            if (state[SDL_SCANCODE_W]) {if(jump1==false) {jump1=true; time_jump1=SDL_GetTicks();}}
            if (state[SDL_SCANCODE_S]) {h='2'; kick_t1=SDL_GetTicks()+100;
                                        if(x_ball+25>x_cat1+80 && x_ball+25<x_cat1+160 && y_ball+25>y_cat1+40 && y_ball+25<y_cat1+70){ball_kick1=true; ball_kick2=false; ball_kick3=false; dx_b=20; v=13; y0_b=y_cat1+60;  Mix_PlayChannel(-1,ball,0);}
                                        if(x_ball+25>x_cat1+80 && x_ball+25<x_cat1+140 && y_ball+25>y_cat1 && y_ball+25<y_cat1+40){ball_kick2=true; ball_kick1=false; ball_kick3=false; dx_b=17; v=19; y0_b=y_cat1+40;  Mix_PlayChannel(-1,ball,0);}
                                        if(x_ball+25>x_cat1+80 && x_ball+25<x_cat1+140 && y_ball+25>y_cat1+70 && y_ball+25<y_cat1+110){ball_kick3=true; ball_kick1=false; ball_kick2=false; dx_b=15; v=13; t=13; y0_b=y_cat1+80;  Mix_PlayChannel(-1,ball,0);}}
            if(state[SDL_SCANCODE_B]) if(pow1==200) {Mix_PlayChannel(-1,power,0); pow_line1=SDL_GetTicks()+20000; Q1=rand()%4;}
            }
            if(star2==false)
            {if (state[SDL_SCANCODE_RIGHT]) if(x_cat2<870) x_cat2+=10;
            if (state[SDL_SCANCODE_LEFT]) if(x_cat2>x_cat1+160) x_cat2-=10;
            if (state[SDL_SCANCODE_UP]) {if(jump2==false) {jump2=true; time_jump2=SDL_GetTicks();}}
            if (state[SDL_SCANCODE_DOWN]) {j='2'; kick_t2=SDL_GetTicks()+100;
                                            if(x_ball+25>x_cat2-70 && x_ball+25<x_cat2+10 && y_ball+25>y_cat2+40 && y_ball+25<y_cat2+70){ball_kick1=true; ball_kick2=false; ball_kick3=false; dx_b=-20; v=13; y0_b=y_cat2+60;  Mix_PlayChannel(-1,ball,0);}
                                            if(x_ball+25>x_cat2-70 && x_ball+25<x_cat2-10 && y_ball+25>y_cat2 && y_ball+25<y_cat2+40) {ball_kick2=true; ball_kick1=false; ball_kick3=false; dx_b=-17; v=19; y0_b=y_cat2+40;  Mix_PlayChannel(-1,ball,0);}
                                            if(x_ball+25>x_cat2-70 && x_ball+25<x_cat2-10 && y_ball+25>y_cat2+70 && y_ball+25<y_cat2+110) {ball_kick3=true; ball_kick1=false; ball_kick2=false; dx_b=-15; v=13; t=13; y0_b=y_cat2+80;  Mix_PlayChannel(-1,ball,0);}}
            if(state[SDL_SCANCODE_P]) if(pow2==200) {Mix_PlayChannel(-1,power,0); pow_line2=SDL_GetTicks()+20000; Q2=rand()%4;}
            }


            if(state[SDL_SCANCODE_ESCAPE]) {Mix_PlayChannel(-1,click,0); pause=true; pause_time=SDL_GetTicks();
                                            while(pause)
                                                {window_color(m_renderer,0,0,0);
                                                textRGBA(m_renderer,200,200,"Press Enter to continue game",2,40,200,200,200,255);
                                                textRGBA(m_renderer,200,400,"Press Escape to quit game",2,40,200,200,200,255);

                                                SDL_RenderPresent(m_renderer);

                                                SDL_Event *f = new SDL_Event();
                                                if( SDL_PollEvent(f))
                                                    {
                                                    const Uint8 *sta = SDL_GetKeyboardState(NULL);
                                                    if (sta[SDL_SCANCODE_ESCAPE]) {pause=false; game=false;

                                                                                    }
                                                    if (sta[SDL_SCANCODE_RETURN]) {pause=false; start_time+=SDL_GetTicks()-pause_time; }
                                                    }
                                                }

                                            }}
          }
           //Game




           while(finish)
           {
               texture(m_renderer,0,0,"background.jpg",1120,703);
               if(g1>g2) {texture(m_renderer,400,150,player1_skin,300,300);
                          rect(m_renderer,380,450,350,50,0,0,0,1);  textRGBA(m_renderer,400,450,"Winner!! (player1)",2,40,255,255,255,255);}
               else if(g1<g2) {texture(m_renderer,400,150,player2_skin,300,300);
                          rect(m_renderer,380,450,350,50,0,0,0,1);  textRGBA(m_renderer,400,450,"Winner!! (player2)",2,40,255,255,255,255);}
               else {texture(m_renderer,290,150,player1_skin,270,270);
                          rect(m_renderer,370,450,400,50,0,0,0,1);  texture(m_renderer,550,150,player2_skin,270,270); textRGBA(m_renderer,390,450,"Equal!! (Don't Fight)",2,40,255,255,255,255);}

               textRGBA(m_renderer,450,550,"Press Enter",2,40,0,0,0,255);
               SDL_RenderPresent(m_renderer);
               SDL_Delay(20);
               SDL_RenderClear(m_renderer);

               if( SDL_PollEvent( event ))
            {
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_RETURN]) {

               if(g1>g2)
    {
        addnumber( s[ 9*pl1 +2] , 3 );
        addnumber( s[ 9*pl1 +3] , 1 );
        addnumber( s[ 9*pl2 +5] , 1 );
    }

    if(g2>g1)
    {
        addnumber( s[ 9*pl2 +2] , 3 );
        addnumber( s[ 9*pl2 +3] , 1 );
        addnumber( s[ 9*pl1 +5] , 1 );
    }


    if(g1==g2)
    {
        addnumber( s[ 9*pl1 +2] , 1 );
        addnumber( s[ 9*pl2 +2] , 1 );
        addnumber( s[ 9*pl1 +4] , 1 );
        addnumber( s[ 9*pl2 +4] , 1 );
    }

if(g1>0)
        {addnumber( s[ 9*pl1 +6] , g1 );
        addnumber( s[ 9*pl2 +7] , g1 );
        }
if(g2>0)
        {addnumber( s[ 9*pl2 +6] , g2 );
        addnumber( s[ 9*pl1 +7] , g2 );
        }


        addnumber( s[ 9*pl1 +9] , 1 );
        addnumber( s[ 9*pl2 +9] , 1 );

    ofstream mylistt;
    int i=0;
    mylistt.open("names.txt");
    for(;i<=9*l;i++)
        mylistt<<s[i]<<endl;
    mylistt<<s[9*i];
    mylistt.close();


    finish=false;} }
           }

           Mix_FreeMusic(background);



        }

}






void my_line(SDL_Renderer *Renderer, int x_1, int y_1, int L, double theta,int widht, int R, int G, int B )

{

    int x_2 = x_1 + L*cos(theta);

    int y_2 = y_1 - L*sin(theta);







    thickLineRGBA(Renderer,x_1,y_1,x_2,y_2,widht,R,G,B,255);

  //  SDL_RenderPresent(Renderer);



}



void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian )

{

    SDL_Rect rectangle ;

    rectangle.x = x;

    rectangle.y = y;

    rectangle.w = w;

    rectangle.h = h;





    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);

    if (fill_boolian==1)

        SDL_RenderFillRect(Renderer, &rectangle);

    SDL_RenderDrawRect(Renderer, &rectangle);

   // SDL_RenderPresent(Renderer);



}



void ellipse(SDL_Renderer *Renderer, int x, int y, int Radius1, int Radius2, int R, int G, int B, int fill_boolian)

{

    if(fill_boolian==1)
        filledEllipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);

    if(fill_boolian==0)

        ellipseRGBA(Renderer,x,y,Radius1,Radius2,R,G,B,255);

   // SDL_RenderPresent(Renderer);

}



void window_color(SDL_Renderer *Renderer, int R, int G, int B)

{

    SDL_SetRenderDrawColor( Renderer, R, G, B, 255 );

    SDL_RenderClear( Renderer );



    // Show the window

  //SDL_RenderPresent( Renderer );



}

void texture(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height)
{
        int n = addressOfImage.length();
        char char_array[n+1];

        strcpy(char_array, addressOfImage.c_str());
        SDL_Texture *myTexture;
        myTexture = IMG_LoadTexture( m_renderer, char_array);
        int w1, h1;
        SDL_QueryTexture(myTexture, NULL, NULL, &w1, &h1);
        SDL_Rect texr1;
        texr1.x = xp;
        texr1.y = yp;
        texr1.w = width;
        texr1.h = height;
        SDL_RenderCopy( m_renderer, myTexture, NULL, &texr1);
            SDL_DestroyTexture(myTexture);
}

int jump(double y, double t)
{   t/=50;
    y=1.2*t*t-20*t+470;
    return y;
}


double move_yball(double t,int v,double y)
    {
        y+=0.5*t*t-v*t;
        return y;
    }

void goal_cel(SDL_Renderer *m_renderer, double x,char c1,char c2)
                                    {for(int i=1;i<=15;i++)
                                            {string pic="goal.png",I;
                                            stringstream s;
                                            s<<i;
                                            s>>I;
                                            pic=I+pic;

                                            string player1_skin="cat1_", player2_skin="cat2_";
                                            player1_skin.push_back(c1); player2_skin.push_back(c2);
                                            player1_skin+=".png"; player2_skin+=".png";


                                        string tail1="tail1_", tail2="tail2_";
                                        tail1.push_back(c1); tail2.push_back(c2);
                                        tail1+="1.png"; tail2+="1.png";

                                            texture(m_renderer,0,0,"background.jpg",1120,703);

                                            texture(m_renderer,200+70,480+30,tail1,60,60);
                                            texture(m_renderer,820-40,480+30,tail2,60,60);
                                            texture(m_renderer,200,480,player1_skin,90,90);
                                            texture(m_renderer,820,480,player2_skin,90,90);

                                            texture(m_renderer,x,510,"ball.png",50,50);

                                            texture(m_renderer,115,370,"gate1.png",90,220);
                                            texture(m_renderer,910,370,"gate2.png",90,220);
                                            texture(m_renderer,0,0,pic,1120,400);

                                            SDL_RenderPresent(m_renderer);
                                            SDL_Delay(90);
                                            SDL_RenderClear(m_renderer);}
}

int stringtoint(string n)
{
    int i=0;
    for(int j=0 ; n.size()-1 >= j  ;  j++)
        {
            i *= 10 ;
            i += n[j]-'0';
        }

    return i;
}


void inttostring (string &s , int a)
{
    s="";
    int m;

    while(a>0)
    {

        s+=a%10 + '0' ;
        a/=10;

    }


    reverseStr(s);
}




void reverseStr(string& str)
{
    int n = str.length();

    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}


void addnumber (string &s , int a)
{
    int m;
    m=stringtoint(s);
    m+=a;
    inttostring(s,m);
}

bool spacetest (string s1,string s2)
{
    //check if s2 has just one space more than s1
    bool flag=true;
    int l1,l2;
    l1=s1.length();
    l2=s2.length();

    if(s2[0]==' ')
        if(l2-l1==1)
        {
            for(int i=0 ; i<l1&& i<l2 && flag ; i++)
                if(s1[i]!=s2[i+1])
                    flag = false;
        }
    if(flag)
        return true;

    return false;
}

