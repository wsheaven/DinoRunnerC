#include <iostream>
#include <Windows.h>



using namespace std;

// Create the dino class 

class Dino
{
public: 
    // Set x and set y methods. They will take the x and y position of the cursor and 
    // set them to the x and y variables. 
    double setX() {
        POINT pos;
        GetCursorPos(&pos);
        x = (pos.x * 10 / 8) + 200;
        cout << "X is set" << endl;
        return 0;
    }

    double setY() {
        POINT pos;
        GetCursorPos(&pos);
        y = pos.y * 10 / 8;
        cout << "Y is set" << endl;
        return 0;
    }

    // Member method to determine if the dinosour should jump.
    // It will take the R value of the pixel at the x and y coordinates. 
    // if the value is 83 or 172 then it means an obstacle has been detected. 
    // If an obstacle has been detected then return true, otherwise return false. 

    bool detect() {
        HDC hDC = GetDC(NULL);
        COLORREF color = GetPixel(hDC, x + 2, y);
        R = GetRValue(color);
        ReleaseDC(NULL, hDC);
        if (R == 83 or R == 172)
        {
            return TRUE; 
        }
        else
        {
            return FALSE;
        }
        
    }
    // Member method to jump. send the key press and then wait 200ms and then release the key. 

    void jump() {
        INPUT space = { 0 };
        space.type = INPUT_KEYBOARD;
        space.ki.wVk = VK_SPACE;
        SendInput(1, &space, sizeof(INPUT)); 
        Sleep(200);
        space.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &space, sizeof(INPUT)); 
            }

    
private:

    // Init member variables and set them to private so only 
    // members of the class may access them. 
    int x = 0;
    int y = 0;
    int R = 0;

};


int main(){

    // Create an object of the Dino class named dino 
    Dino dino; 

    // User will place their cursor on the dinosours arm and then press a. 
    // Once this happens the methods setx and sety will be called and set the 
    // location of the pixel to be checked. 
    bool start = TRUE;
    while (start)
    {
        if (GetKeyState('A') & 0x8000)
        {
            dino.setX();
            dino.setY();
            cout << "Dino nose has been init";
            start = FALSE;
        }
    }

    // Print to the terminal to show that the arm of the dinosour has been init
    cout << "Game Time";

    // main loop that detects obstacles and jumps if needed. 
    while (1) {

        // if the method detect returns true it means an object is incoming 
        // and thus the dinosour should jump. 
        if (dino.detect())
        {
            dino.jump();
        }
    }

    return 0;
}