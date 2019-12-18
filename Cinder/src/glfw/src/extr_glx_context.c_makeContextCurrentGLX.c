#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * handle; int /*<<< orphan*/  window; } ;
struct TYPE_9__ {TYPE_1__ glx; } ;
struct TYPE_11__ {TYPE_2__ context; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_10__ {int /*<<< orphan*/  display; } ;
struct TYPE_12__ {TYPE_3__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  None ; 
 TYPE_7__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwPlatformSetCurrentContext (TYPE_4__*) ; 
 int /*<<< orphan*/  glXMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void makeContextCurrentGLX(_GLFWwindow* window)
{
    if (window)
    {
        if (!glXMakeCurrent(_glfw.x11.display,
                            window->context.glx.window,
                            window->context.glx.handle))
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "GLX: Failed to make context current");
            return;
        }
    }
    else
    {
        if (!glXMakeCurrent(_glfw.x11.display, None, NULL))
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "GLX: Failed to clear current context");
            return;
        }
    }

    _glfwPlatformSetCurrentContext(window);
}