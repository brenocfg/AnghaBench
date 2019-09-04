#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int GLUT_DOWN ; 
 int GLUT_LEFT_BUTTON ; 
 int GLUT_UP ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int touch_ended_button ; 
 int touch_ended_x ; 
 int touch_ended_y ; 
 int touch_started_button ; 
 int touch_started_x ; 
 int touch_started_y ; 

void mouseCB(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            printf("GLUT_DOWN: button: %d, x: %d, y: %d\n", button, x, y);
            touch_started_button = button;
            touch_started_x = x;
            touch_started_y = y;
        }
        else if(state == GLUT_UP)
        {
            printf("GLUT_UP: button: %d, x: %d, y: %d\n", button, x, y);
            touch_ended_button = button;
            touch_ended_x = x;
            touch_ended_y = y;
        }
    }
}