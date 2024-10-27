#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>


#define BET_AM 3
#define MAX_NUMS 17

int main(void)
{

    Color colors[MAX_NUMS] = {
        BLACK,RED,BLACK,RED,BLACK,RED,BLACK
        ,RED,BLACK,GREEN,BLACK,RED,BLACK,RED,
        BLACK,RED,GREEN };
    
    Color betColors[BET_AM] = {
        BLACK,GREEN,RED};


    Rectangle colorsRecs[MAX_NUMS] = {0};
    Rectangle betRecs[BET_AM] = {0};

    const int screenWidth = 1000;
    const int screenHeight = 600;

    for (int i = 0; i < MAX_NUMS; i++)
    {
        colorsRecs[i].x = -10 + 60.0f*i + 2*i;
        colorsRecs[i].y = 250;
        colorsRecs[i].width = 70;
        colorsRecs[i].height = 60;
    }

    for (int i = 0; i < BET_AM; i++)
    {
        betRecs[i].x = 400 + 60.0f*i + 2*i;
        betRecs[i].y = 150;
        betRecs[i].width = 50;
        betRecs[i].height = 50;
    }

    int currentFPS = 400;
    bool isMoving = true;
    float moveSpeed = 5.0f;
    int stopCounter;
    int colorMouseHover = 0;
    bool shouldSlowDown = false;
    Vector2 mousePosition;


    InitWindow(screenWidth, screenHeight, "cool window 3000");

    SetTargetFPS(currentFPS);

    // Main game loop
    while (!WindowShouldClose())
    {

        mousePosition = GetMousePosition();
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_SPACE) && !isMoving){
            isMoving = !isMoving;
            currentFPS = 400;  // i find this solution to make the animation a bit bad but thats the most i can do right now
            SetTargetFPS(currentFPS); // this entire thing sucks for randomizing but thats not my main focus
            shouldSlowDown = false;
            stopCounter = 0;
        }
        if(isMoving){

            for (int i = 0; i < MAX_NUMS; i++){

            colorsRecs[i].x += moveSpeed;
            
            // screen wrap
                if (colorsRecs[i].x > screenWidth){

                    colorsRecs[i].x = -colorsRecs[i].width + 10; // +10 for spacing
                    shouldSlowDown = true;

                }
            }
        }
        if(shouldSlowDown){
            stopCounter++;
            if(stopCounter <380 && currentFPS > 30){
                currentFPS--;
                SetTargetFPS(currentFPS);
            }
            if(stopCounter >=380 || currentFPS < 35){
                isMoving = false;
                shouldSlowDown = false;
                stopCounter = 0;
            }
        }

        for (int i = 0; i < BET_AM; i++)
        {
            if (CheckCollisionPointRec(mousePosition, betRecs[i]))
            {
                colorMouseHover = i;
                break;
            }
            else colorMouseHover = -1;
        }
    

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
//
            ClearBackground(RAYWHITE);
            // the spinning stuff
            for (int i = 0; i < MAX_NUMS; i++)
            {
                DrawRectangleRec(colorsRecs[i], colors[i]);
            }

            // buttons
            for (int i = 0; i < BET_AM; i++)
            {
                DrawRectangleRec(betRecs[i], (i == colorMouseHover) ? Fade(WHITE, 0.1f) : betColors[i]);
                DrawRectangleLinesEx(betRecs[i], 1, BLACK);
            }

            DrawText("PRESS SPACE TO SPIN", 375, 400, 20, BLACK);




        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();

    return 0;
}