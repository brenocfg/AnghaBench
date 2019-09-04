#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ cursorMode; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  XEvent ;
struct TYPE_6__ {int /*<<< orphan*/  display; } ;
struct TYPE_8__ {TYPE_2__* cursorWindow; TYPE_1__ x11; } ;

/* Variables and functions */
 scalar_t__ GLFW_CURSOR_DISABLED ; 
 int /*<<< orphan*/  XNextEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int XPending (int /*<<< orphan*/ ) ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwPlatformGetWindowSize (TYPE_2__*,int*,int*) ; 
 int /*<<< orphan*/  _glfwPlatformSetCursorPos (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  processEvent (int /*<<< orphan*/ *) ; 

void _glfwPlatformPollEvents(void)
{
    int count = XPending(_glfw.x11.display);
    while (count--)
    {
        XEvent event;
        XNextEvent(_glfw.x11.display, &event);
        processEvent(&event);
    }

    _GLFWwindow* window = _glfw.cursorWindow;
    if (window && window->cursorMode == GLFW_CURSOR_DISABLED)
    {
        int width, height;
        _glfwPlatformGetWindowSize(window, &width, &height);
        _glfwPlatformSetCursorPos(window, width / 2, height / 2);
    }
}