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
struct TYPE_7__ {int /*<<< orphan*/  handle; } ;
struct TYPE_8__ {TYPE_2__ x11; } ;
typedef  TYPE_3__ _GLFWwindow ;
typedef  int /*<<< orphan*/  XEvent ;
struct TYPE_6__ {int /*<<< orphan*/  display; } ;
struct TYPE_9__ {TYPE_1__ x11; } ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  VisibilityNotify ; 
 int /*<<< orphan*/  XCheckTypedWindowEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  waitForEvent (double*) ; 

__attribute__((used)) static GLFWbool waitForVisibilityNotify(_GLFWwindow* window)
{
    XEvent dummy;
    double timeout = 0.1;

    while (!XCheckTypedWindowEvent(_glfw.x11.display,
                                   window->x11.handle,
                                   VisibilityNotify,
                                   &dummy))
    {
        if (!waitForEvent(&timeout))
            return GLFW_FALSE;
    }

    return GLFW_TRUE;
}