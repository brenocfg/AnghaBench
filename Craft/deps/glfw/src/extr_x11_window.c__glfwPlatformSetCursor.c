#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  handle; } ;
struct TYPE_12__ {scalar_t__ cursorMode; TYPE_2__ x11; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_9__ {int /*<<< orphan*/  handle; } ;
struct TYPE_13__ {TYPE_1__ x11; } ;
typedef  TYPE_5__ _GLFWcursor ;
struct TYPE_11__ {int /*<<< orphan*/  display; } ;
struct TYPE_14__ {TYPE_3__ x11; } ;

/* Variables and functions */
 scalar_t__ GLFW_CURSOR_NORMAL ; 
 int /*<<< orphan*/  XDefineCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUndefineCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__ _glfw ; 

void _glfwPlatformSetCursor(_GLFWwindow* window, _GLFWcursor* cursor)
{
    if (window->cursorMode == GLFW_CURSOR_NORMAL)
    {
        if (cursor)
            XDefineCursor(_glfw.x11.display, window->x11.handle, cursor->x11.handle);
        else
            XUndefineCursor(_glfw.x11.display, window->x11.handle);

        XFlush(_glfw.x11.display);
    }
}