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
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int GLFW_MOUSE_BUTTON_LEFT ; 
 int GLFW_PRESS ; 
 int active_view ; 
 int do_redraw ; 
 int height ; 
 int width ; 
 int xpos ; 
 int ypos ; 

__attribute__((used)) static void mouseButtonFun(GLFWwindow* window, int button, int action, int mods)
{
    if ((button == GLFW_MOUSE_BUTTON_LEFT) && action == GLFW_PRESS)
    {
        // Detect which of the four views was clicked
        active_view = 1;
        if (xpos >= width / 2)
            active_view += 1;
        if (ypos >= height / 2)
            active_view += 2;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        // Deselect any previously selected view
        active_view = 0;
    }

    do_redraw = 1;
}