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
struct TYPE_6__ {scalar_t__ major; scalar_t__ minor; } ;
struct TYPE_7__ {TYPE_1__ context; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_8__ {scalar_t__ major; scalar_t__ minor; } ;
typedef  TYPE_3__ _GLFWctxconfig ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_VERSION_UNAVAILABLE ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* _glfwPlatformGetCurrentContext () ; 

GLboolean _glfwIsValidContext(const _GLFWctxconfig* ctxconfig)
{
    _GLFWwindow* window = _glfwPlatformGetCurrentContext();

    if (window->context.major < ctxconfig->major ||
        (window->context.major == ctxconfig->major &&
         window->context.minor < ctxconfig->minor))
    {
        // The desired OpenGL version is greater than the actual version
        // This only happens if the machine lacks {GLX|WGL}_ARB_create_context
        // /and/ the user has requested an OpenGL version greater than 1.0

        // For API consistency, we emulate the behavior of the
        // {GLX|WGL}_ARB_create_context extension and fail here

        _glfwInputError(GLFW_VERSION_UNAVAILABLE, NULL);
        return GL_FALSE;
    }

    return GL_TRUE;
}