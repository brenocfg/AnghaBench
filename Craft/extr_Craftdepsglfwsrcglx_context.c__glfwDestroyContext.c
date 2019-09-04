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
struct TYPE_7__ {int /*<<< orphan*/ * context; int /*<<< orphan*/ * visual; } ;
struct TYPE_8__ {TYPE_2__ glx; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_6__ {int /*<<< orphan*/  display; } ;
struct TYPE_9__ {TYPE_1__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFree (int /*<<< orphan*/ *) ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfw_glXDestroyContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void _glfwDestroyContext(_GLFWwindow* window)
{
    if (window->glx.visual)
    {
        XFree(window->glx.visual);
        window->glx.visual = NULL;
    }

    if (window->glx.context)
    {
        _glfw_glXDestroyContext(_glfw.x11.display, window->glx.context);
        window->glx.context = NULL;
    }
}