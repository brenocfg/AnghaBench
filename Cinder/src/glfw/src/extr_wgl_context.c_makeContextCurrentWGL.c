#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * handle; int /*<<< orphan*/ * dc; } ;
struct TYPE_7__ {TYPE_1__ wgl; } ;
struct TYPE_8__ {TYPE_2__ context; } ;
typedef  TYPE_3__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwPlatformSetCurrentContext (TYPE_3__*) ; 
 scalar_t__ wglMakeCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void makeContextCurrentWGL(_GLFWwindow* window)
{
    if (window)
    {
        if (wglMakeCurrent(window->context.wgl.dc, window->context.wgl.handle))
            _glfwPlatformSetCurrentContext(window);
        else
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "WGL: Failed to make context current");
            _glfwPlatformSetCurrentContext(NULL);
        }
    }
    else
    {
        if (!wglMakeCurrent(NULL, NULL))
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "WGL: Failed to clear current context");
        }

        _glfwPlatformSetCurrentContext(NULL);
    }
}