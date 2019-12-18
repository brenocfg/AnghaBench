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
 int active_view ; 
 int do_redraw ; 
 int /*<<< orphan*/  glfwGetFramebufferSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int*,int*) ; 
 int rot_x ; 
 int rot_y ; 
 int rot_z ; 
 double xpos ; 
 double ypos ; 

__attribute__((used)) static void cursorPosFun(GLFWwindow* window, double x, double y)
{
    int wnd_width, wnd_height, fb_width, fb_height;
    double scale;

    glfwGetWindowSize(window, &wnd_width, &wnd_height);
    glfwGetFramebufferSize(window, &fb_width, &fb_height);

    scale = (double) fb_width / (double) wnd_width;

    x *= scale;
    y *= scale;

    // Depending on which view was selected, rotate around different axes
    switch (active_view)
    {
        case 1:
            rot_x += (int) (y - ypos);
            rot_z += (int) (x - xpos);
            do_redraw = 1;
            break;
        case 3:
            rot_x += (int) (y - ypos);
            rot_y += (int) (x - xpos);
            do_redraw = 1;
            break;
        case 4:
            rot_y += (int) (x - xpos);
            rot_z += (int) (y - ypos);
            do_redraw = 1;
            break;
        default:
            // Do nothing for perspective view, or if no view is selected
            break;
    }

    // Remember cursor position
    xpos = x;
    ypos = y;
}