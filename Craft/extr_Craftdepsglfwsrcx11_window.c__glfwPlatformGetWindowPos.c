#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  handle; } ;
struct TYPE_8__ {TYPE_1__ x11; } ;
typedef  TYPE_3__ _GLFWwindow ;
typedef  scalar_t__ Window ;
struct TYPE_7__ {int /*<<< orphan*/  display; scalar_t__ root; } ;
struct TYPE_9__ {TYPE_2__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  XTranslateCoordinates (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,scalar_t__*) ; 
 TYPE_5__ _glfw ; 

void _glfwPlatformGetWindowPos(_GLFWwindow* window, int* xpos, int* ypos)
{
    Window child;
    int x, y;

    XTranslateCoordinates(_glfw.x11.display, window->x11.handle, _glfw.x11.root,
                          0, 0, &x, &y, &child);

    if (child)
    {
        int left, top;
        XTranslateCoordinates(_glfw.x11.display, window->x11.handle, child,
                              0, 0, &left, &top, &child);

        x -= left;
        y -= top;
    }

    if (xpos)
        *xpos = x;
    if (ypos)
        *ypos = y;
}