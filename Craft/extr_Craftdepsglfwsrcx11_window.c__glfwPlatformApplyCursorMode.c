#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cursorMode; } ;
typedef  TYPE_1__ _GLFWwindow ;

/* Variables and functions */
#define  GLFW_CURSOR_DISABLED 130 
#define  GLFW_CURSOR_HIDDEN 129 
#define  GLFW_CURSOR_NORMAL 128 
 int /*<<< orphan*/  disableCursor (TYPE_1__*) ; 
 int /*<<< orphan*/  hideCursor (TYPE_1__*) ; 
 int /*<<< orphan*/  restoreCursor (TYPE_1__*) ; 

void _glfwPlatformApplyCursorMode(_GLFWwindow* window)
{
    switch (window->cursorMode)
    {
        case GLFW_CURSOR_NORMAL:
            restoreCursor(window);
            break;
        case GLFW_CURSOR_HIDDEN:
            hideCursor(window);
            break;
        case GLFW_CURSOR_DISABLED:
            disableCursor(window);
            break;
    }
}