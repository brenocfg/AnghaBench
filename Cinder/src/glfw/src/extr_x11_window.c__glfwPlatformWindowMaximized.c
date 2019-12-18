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
struct TYPE_7__ {scalar_t__ NET_WM_STATE_MAXIMIZED_VERT; scalar_t__ NET_WM_STATE_MAXIMIZED_HORZ; int /*<<< orphan*/  NET_WM_STATE; } ;
struct TYPE_9__ {TYPE_2__ x11; } ;
typedef  int GLFWbool ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int GLFW_FALSE ; 
 int GLFW_TRUE ; 
 int /*<<< orphan*/  XA_ATOM ; 
 int /*<<< orphan*/  XFree (scalar_t__*) ; 
 TYPE_5__ _glfw ; 
 unsigned long _glfwGetWindowPropertyX11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char**) ; 

int _glfwPlatformWindowMaximized(_GLFWwindow* window)
{
    Atom* states;
    unsigned long i;
    GLFWbool maximized = GLFW_FALSE;
    const unsigned long count =
        _glfwGetWindowPropertyX11(window->x11.handle,
                                  _glfw.x11.NET_WM_STATE,
                                  XA_ATOM,
                                  (unsigned char**) &states);

    for (i = 0;  i < count;  i++)
    {
        if (states[i] == _glfw.x11.NET_WM_STATE_MAXIMIZED_VERT ||
            states[i] == _glfw.x11.NET_WM_STATE_MAXIMIZED_HORZ)
        {
            maximized = GLFW_TRUE;
            break;
        }
    }

    XFree(states);
    return maximized;
}