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
typedef  float GLfloat ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_CURSOR ; 
 scalar_t__ GLFW_CURSOR_DISABLED ; 
 float alpha ; 
 float beta ; 
 double cursorX ; 
 double cursorY ; 
 scalar_t__ glfwGetInputMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cursor_position_callback(GLFWwindow* window, double x, double y)
{
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
    {
        alpha += (GLfloat) (x - cursorX) / 10.f;
        beta += (GLfloat) (y - cursorY) / 10.f;

        cursorX = x;
        cursorY = y;
    }
}