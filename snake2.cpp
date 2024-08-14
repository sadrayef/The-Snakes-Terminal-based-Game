#include <iostream>
using namespace std;
#include <stdlib.h>
#include <limits>
#include <string>
#include "clui.h"
#include <chrono>
#include <thread>
#include <vector>
#include<time.h>
using namespace std::this_thread; 
using namespace std::chrono;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 
//                              ~~~~~~~~~~~~~~~~~~~O The SNAKE'S! @++++++++++++++++++++
// 
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//                            Sadra Yosefabadi - 402243114 - yosefabadisadra@gmail.com 
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
std::vector<std::string> names; int points[100] ;   bool lost = true ; bool game = true; char direct,m1,m2; int ch; int tip =0;
const int tool = 20 , arz = 40;  int counter =  0; int e,r,c=0,w=0,u=0; int diff =0;
struct fruit{int x ,y;} f1,f2;
struct snake{string name; int point = 0 ; int x,y,s; } s1,s2; 
struct bomb{int x,y;}b1;
enum edir {stop =0 ,UP ,DOWN , LEFT , RIGHT}; edir dir1 ,dir2; void opt1(); void console();
int tailx[100],taily[100],ntail = 3 ;
int buttx[100],butty[100],nbutt = 3 ;
string p1="1"; string p2="2"; string p3="3"; string p4="4";  
int s = 0 , m = 0;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void swap(int &x, int &y) {
int temp = x; /* save the value at address x */ x = y; /* put y into x */
y = temp; /* put x into y */
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void swapper(string &x, string &y) {
string temp = x; /* save the value at address x */ x = y; /* put y into x */
y = temp; /* put x into y */
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void bubble_sort(int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (points[j + 1] > points[j]) { // Change the condition to sort in descending order
                // Swap the points
                int temp = points[j];
                points[j] = points[j + 1];
                points[j + 1] = temp;

                // Swap the corresponding names
                // Assuming 'names' is an array of strings
                string tempName = names[j];
                names[j] = names[j + 1];
                names[j + 1] = tempName;
            }
        }
    }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void speed(){
    cout << "\n";
    system("CLEAR");
    cout << "\n\n                                                               Choose difficulty :";
    cout << "\n\n\n                                                               1.Super easy\n                                                               2.Easy\n                                                               3.Medium\n                                                               4.Hard\n                                                               5.Extremely Hard\n";
    cout <<"\n\n\n                                                               Your choose :";
    cin >> diff;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void map(){ 
    system("ClEAR");
    cout << "\n\n\n\n                                                                             ";
    for (int i=0;i<arz;i++){
        change_color_rgb(153, 0, 0);
        cout << "#" ;
        reset_color();}
    cout << endl;
    for(int i=0;i<tool;i++)
    { cout << "                                                                             ";
        for (int j=0;j<arz;j++)
        {
            if(j==0 || j == arz-1){
                change_color_rgb(153, 0, 0);
            cout << "#"; 
            reset_color();}
            else if(i==s1.y && j ==s1.x){
                change_color_rgb(102, 255, 255);
                cout << "@";
                reset_color();
            }else if(i==s2.y && j ==s2.x){
                change_color_rgb(0, 0, 153);
                cout << "O";
                reset_color();
            }else if ((i==f1.x && j==f1.y) ){ 
                change_color_rgb(0, 255, 0);
                cout << "*";
                reset_color();
            }else if( (i==f2.x && j==f2.y)) {
                change_color_rgb(0, 255, 0);
                cout <<"*";
                reset_color();
            }else if (i==b1.x && j==b1.y){
                change_color_rgb(255, 0, 0);
                cout << "B";
                reset_color();
            }else {
                bool print = false;
                for(int k=0;k<ntail;k++)
                {
                    if(j==tailx[k] && i==taily[k])
                    {
                        change_color_rgb(102, 255, 255);
                        cout << "+";
                        print = true;
                        reset_color();
                    }
                }

                for(int s=0;s<nbutt;s++)
                {
                    if(j==buttx[s] && i==butty[s])
                    {
                        change_color_rgb(0, 0, 153);
                        cout << "o";
                        print = true;
                        reset_color();
                    }
                }
                if(!print) cout << " ";
                
                
                }
        }
        cout << endl; 
    } 
      cout << "                                                                             ";
    for (int i=0;i<arz;i++)
    {change_color_rgb(153, 0, 0);
        cout << "#";
        reset_color();
        }
    cout << endl; 

    cout <<"\n\n\n                                                                            -------------------------------------------";
    if (s1.point >= s2.point){
        cout << "\n                                                                            1." << s1.name << " = " << s1.point;
        cout << "\n                                                                            -------------------------------------------";
        cout << "\n                                                                            2." << s2.name << " = " << s2.point;
        cout << "\n                                                                            -------------------------------------------\n";
    }else {
        cout << "\n                                                                            1." << s2.name << " = " << s2.point;
        cout << "\n                                                                            -------------------------------------------";
        cout << "\n                                                                            2." << s1.name << " = " << s1.point;
        cout << "\n                                                                            -------------------------------------------\n";
    }

    //cout << b1.x << " " << b1.y;
    //cout << nbutt;
    //cout << d1;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void rungame() { 
     dir1 = stop; lost = true;
    s1.x = 14; s2.x = 26; s1.y = 10; s2.y = 10;

    f1.x = (rand() %19) +1; 
    f1.y = (rand() %38) +1;
    f2.x = (rand() %19) +1; 
    f2.y = (rand() %38) +1; 

    b1.x = (rand() %19) +1;
    b1.y = (rand() %38) +1;

    while(( (f2.x == f1.x)&&(f2.y == f1.y) )){
        f1.x = (rand() %19) +1; 
        f1.y = (rand() %38) +1;
    }
   
    while((b1.x==f1.x)&&(b1.y==f1.y) || (b1.x==f2.x)&&(b1.y==f2.y)){
        b1.x = (rand() %19) +1;
        b1.y = (rand() %38) +1;
   }

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void direction(){ 
    if(is_keyboard_hit()) { switch (getch()){  //kbhit getch 

        case 119: if(dir1!=DOWN){ dir1 = UP;} break; case 87: if(dir1!=DOWN){ dir1 = UP;} break;
        case 115: if(dir1!=UP){ dir1 = DOWN;} break; case 83: if(dir1!=UP){ dir1 = DOWN;} break; 
        case 97: if(dir1!=RIGHT){ dir1 = LEFT; }break; case 65: if(dir1!=RIGHT){ dir1 = LEFT;} break; 
        case 100: if(dir1!=LEFT){ dir1 = RIGHT; } break; case 68: if(dir1!=LEFT){ dir1 = RIGHT; } break;
        //-------- 
        case 105: if(dir2!=DOWN){ dir2 = UP;} break; case 73: if(dir2!=DOWN){ dir2 = UP;} break;
        case 107: if(dir2!=UP){ dir2 = DOWN;} break;  case 75: if(dir2!=UP){ dir2 = DOWN;} break; 
        case 106: if(dir2!=RIGHT){ dir2 = LEFT;} break; case 74: if(dir2!=RIGHT){ dir2 = LEFT;} break;
        case 108: if(dir2!=LEFT){ dir2 = RIGHT; } break; case 76: if(dir2!=LEFT){ dir2 = RIGHT; } break;
        default : break;
    }}}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void movement(){ 

    int prevx = tailx[0];
    int prevy = taily[0];
    tailx[0]=s1.x;
    taily[0]=s1.y;
    int perv2x ,prev2y;

    for(int i=1;i< ntail;i++)
    {
         perv2x = tailx[i];
         prev2y = taily[i];
         tailx[i] = prevx;
         taily[i] = prevy;
         prevx = perv2x;
         prevy = prev2y; 
    }

    //cout << d1;
    switch (dir1){ 
        case UP : s1.y--; break;
        case DOWN :  s1.y++; break;
        case LEFT :  s1.x--; break;
        case RIGHT :  s1.x++; break;
        default : break;}

        if( (s1.x == f1.y)&&(s1.y == f1.x) )
        { 
            s1.point += 10; ntail +=1; cout << '\a';
            f1.y = (rand() %38) +1; 
            f1.x = (rand() %19) +1; 
            while((f2.x == f1.x)&&(f2.y == f1.y))
            {
                f1.y = (rand() %38) +1;
                f1.x = (rand() %19) +1; 
            }
        }
        else if((s1.x == f2.y)&&(s1.y == f2.x) )
        { 
            s1.point += 10; ntail +=1; cout << '\a';
            f2.y = (rand() %38) +1; 
            f2.x = (rand() %19) +1; 
            while((f2.x == f1.x)&&(f2.y == f1.y))
            {
                f2.y = (rand() %38) +1;
                f2.x = (rand() %19) +1; 
            }
        }
        if(s1.y < 0 || s1.y > 19 || s1.x < 1 || s1.x > 38 || ((s1.x == b1.y) && (s1.y == b1.x)) || ((s1.x == s2.x) && (s1.y == s2.y))){
            lost = false ; cout << '\a';
        }
        for(int i=3;i<ntail;i++)
        {
            if(s1.x==tailx[i] && s1.y==taily[i])
            {
                lost = false ; cout << '\a';
            }
        }

        for(int i=0;i<nbutt;i++)
        {
            if(s1.x==buttx[i] && s1.y==butty[i])
            {
                lost = false ; cout << '\a';
            }
        }
        
        } 
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void movement2(){

    int backx = buttx[0];
    int backy = butty[0];
    buttx[0]=s2.x;
    butty[0]=s2.y;
    int back2x ,back2y;

    for(int i=1;i< nbutt;i++)
    {
         back2x = buttx[i];
         back2y = butty[i];
         buttx[i] = backx;
         butty[i] = backy;
         backx = back2x;
         backy = back2y; 
    }

    switch (dir2){
        case UP : s2.y--; break;
        case DOWN : s2.y++; break;
        case LEFT : s2.x--; break;
        case RIGHT : s2.x++; break;
        default : break;} 

        if( (s2.x == f1.y)&&(s2.y == f1.x) )
        { 
            s2.point += 10; nbutt +=1; cout << '\a';
            f1.y = (rand() %38) +1; 
            f1.x = (rand() %19) +1; 
            while((f2.x == f1.x)&&(f2.y == f1.y))
            {
                f1.y = (rand() %38) +1 ;
                f1.x = (rand() %19) +1 ; 
            }
        }
        else if((s2.x == f2.y)&&(s2.y == f2.x) )
        { 
            s2.point += 10; nbutt +=1; cout << '\a';
            f2.y = (rand() %38) +1; 
            f2.x = (rand() %19) +1; 
            while((f2.x == f1.x)&&(f2.y == f1.y))
            {
                f2.y = (rand() %38) +1;
                f2.x = (rand() %19) +1; 
            }
        }

        if(s2.y < 0 || s2.y > 19 || s2.x < 1 || s2.x > 38 || ((s2.x == b1.y) && (s2.y == b1.x))|| ((s1.x == s2.x) && (s1.y == s2.y))){
            lost = false; cout << '\a';
        }

        for(int i=3;i<nbutt;i++)
        {
            if(s2.x==buttx[i] && s2.y==butty[i])
            {
                lost = false ; cout << '\a';
            }
        }

        for(int i=0;i<ntail;i++)
        {
            if(s2.x==tailx[i] && s2.y==taily[i])
            {
                lost = false ; cout << '\a';
            }
        }
    }
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void list(){
    for (size_t i = 0; i < names.size(); ++i) {
            std::cout <<"                                                               " << i + 1 << ". " << names[i] << std::endl;
        }
        cout << "\n                                                               Please enter the first players number : ";
        cin >> e;
        cout << "\n";
        cout << "                                                               Please enter the second players number : ";
        cin >> r;
        cout << "\n";
        if(e == r){
            cout <<"\n                                                               WARNING !!!  Choose two different players.";
            cin.clear(); 
            system("CLEAR"); cout << "\n\n"; opt1();
        } 
        s1.name = names[e]; s2.name = names[r];
        //hooseskin();
        speed();
        
    }
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void opt3(){
if(counter==0){
cout <<"\n\n                                                               Error!!!!  There is no saved players!.\n";
cout << "\n";
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
sleep_until(system_clock::now() + seconds(1));
system("CLEAR");
console();
}else{
    list();
}

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void opt12(){
    cout << "\n                                                               Please enter the first players name : ";
    cin >> s1.name;
    cout << "\n";
    cout << "                                                               Please enter the second players name : ";
    cin >> s2.name;
    cout << "\n";
    if(s1.name == s2.name){
        cout <<"\n                                                               WARNING !!!  Enter two different usernames.";
        cin.clear(); 
        system("CLEAR"); cout << "\n\n"; opt1();
    } 
    counter ++;
    names.push_back(s1.name);
    names.push_back(s2.name); 
    counter ++;
    
    speed();
    
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
void opt1(){
    cout <<"\n                                                               Please choose an option : \n\n";
    cout <<"\n                                                               1.Play with new users\n";
    cout <<"\n                                                               2.Play with saved users"; 
    cout <<"\n\n                                                               ";
    int usr ; cin >> usr ;
    if (cin.fail() || usr < 1 || usr > 2) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout <<"\n\n"; system("CLEAR");
            cout << "\n\n                                                               Error!!!!  Please Choose Again.\n";
            opt1();}
    else{
    if (usr==1){ opt12();}
    if (usr==2){ 
    if(counter == 0){
    system("CLEAR");
    cout <<"\n\n                                                               Error!!!!  There is no saved players!.\n";
    opt1();
    }
    else { list();}
    
}}}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void opt2(){
    if(counter == 0){
    system("CLEAR");
    cout <<"\n\n                                                               Error!!!!  There is no saved players!.\n";
    console();
    }
   bubble_sort(counter);
    for (size_t i = 0; i < names.size(); ++i) {
            std::cout <<"                                                               " << i + 1 << ". " << names[i] <<" : "<< points[i] << std::endl;
        }
    sleep_until(system_clock::now() + seconds(5));
    console();
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void console() {
    int opt;
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    do { 
        change_color_rgb(0, 204, 102);
        cout << "\n                                                                              ~~~~~~~~~~~~~~~~~~~O The SNAKE'S! @++++++++++++++++++++";reset_color(); cout << "\n\n                                                               ____________________________________________________________________________________\n\n                                                               Please choose an option :\n\n                                                               1. Start\n                                                               2. Points Table\n                                                               3. Change the Player\n                                                               4. Exit\n\n                                                               Your choose: ";
        
        cin >> opt;
        if (cin.fail() || opt < 1 || opt > 4) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "\n\n                                                                             Error!!!!  Please Choose Again.\n";
            sleep_until(system_clock::now() + seconds(1));
            system("CLEAR");
        } else {
            switch (opt) {
                case 1:
                    opt1();
                    break;
                case 2:
                    opt2();
                    break;
                case 3:
                    opt3();
                    break;
                case 4:
                    {using namespace std::this_thread; // sleep_for, sleep_until
                    using namespace std::chrono; // nanoseconds, system_clock, seconds
                    cout << "\n\n\n\n                                                                                       Thanks for playing!";
                    sleep_until(system_clock::now() + seconds(1));
                    game = false;
                    break;}
            }
        }

    } while (opt < 1 || opt > 4);
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main() {
    //change_background_color(1);
    while(game){
    init_clui();
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    if(c==0){
    change_color_rgb(255, 153, 204);
    cout << "\n\n\n\n\n\n\n                                                                                               ~~~ Welcome ~~~";
    cout << "\n\n";
    reset_color();
    sleep_until(system_clock::now() + seconds(1));
    }
    else{
    points[counter-2] = s1.point;
    points[counter-1] = s2.point;
        cout << "\n\n\n\n\n\n\n                                                                                               Game over !!";
    cout << "\n\n";
    if(s1.point>s2.point){cout << "                                                                                               The winner is "<< s1.name;}
    else if(s2.point > s1.point){cout  <<  "                                                                                               The winner is "<< s2.name;}
    else if(s2.point==s1.point){cout << "                                                                                               We have two winners!";}
    cout << "\n\n";


    sleep_until(system_clock::now() + seconds(2));
    
    
    }system("CLEAR");
    s1.point = 0; s2.point =0; 
    console();
    if(!game) {system("CLEAR"); break;}
    rungame();
    system("CLEAR");
   change_color_rgb(0, 204, 0);
    cout<<"\n\n\n                                                                                             -----------------\n";                                                                     
    cout <<"                                                                                             |  Loading ...  | \n";
    cout<<"                                                                                             -----------------\n";
    tip = 1 + (rand() % 4);
    reset_color();
    change_color_rgb(255, 153, 204);
    switch (tip){
    case 1 : cout << "\n\n\n                                                                         * Don't hit the walls,Otherwise you are tired of this life!" ; break;
    case 2 : cout << "\n\n\n                                                                         * Beware of the BOMB! It's real!!" ; break;
    case 3 : cout << "\n\n\n                                                                         * Dont itch yourself." ; break;
    case 4 : cout << "\n\n\n                                                                         * Don't kiss the other snake,its poisoned!!\n\n" ; break;
    default: break;
    reset_color();
    }

cout << "\n";

    sleep_until(system_clock::now() + seconds(1));
    cout <<" ";
    sleep_until(system_clock::now() + seconds(1));
    cout <<" ";
    sleep_until(system_clock::now() + seconds(1));
    cout <<" ";
    
    system("CLEAR");
    change_color_rgb(255, 0, 0);
    sleep_until(system_clock::now() + seconds(1));
    cout <<"\n\n\n                                                                                                    1";
    cout <<"\n\n\n\\n";
    reset_color();
    cout << '\a';
    sleep_until(system_clock::now() + seconds(1));
    system("CLEAR");

    change_color_rgb(255, 255, 0);
    cout <<"\n\n\n                                                                                                    2";
    cout <<"\n\n\n\\n";
    cout << '\a';
    reset_color();
    sleep_until(system_clock::now() + seconds(1));
    system("CLEAR");
    change_color_rgb(0, 255, 0);
    cout <<"\n\n\n                                                                                                    3";
    cout <<"\n\n\n\\n";
    cout << '\a';
    reset_color();
    sleep_until(system_clock::now() + seconds(1));
    time_t start = time(NULL);
    while(lost){
        
        //dir1 = stop; dir2 = stop;
        map();
        direction();
        movement();
        movement2();
        switch (diff)
        {
        case 1 : delay(250); break; // very easy
        case 2 : delay(200); break; // easy
        case 3 : delay(150); break; // medium
        case 4 : delay(100); break; // hard
        case 5 : delay(50); break; // extremly hard
        default: delay(150); break;
        }
        time_t taken = time(NULL) - start;
        
        m = taken / 60; 
        s = taken % 60;
        cout<<"\n\n                                                                                        Time taken : "<< m <<':'<<s<<endl;

        } 
       
        sleep_until(system_clock::now() + seconds(2));
        system("CLEAR");
        s1.x = 14; s2.x = 26; s1.y = 10; s2.y = 10;
        dir1 = stop; dir2 = stop;
        ntail = 3; nbutt = 3;
        c +=1;
}

return 0;}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%