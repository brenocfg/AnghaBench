#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * GLFWglproc ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_NO_CURRENT_CONTEXT ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwPlatformGetCurrentContext () ; 
 int /*<<< orphan*/ * _glfwPlatformGetProcAddress (char const*) ; 

GLFWglproc glfwGetProcAddress(const char* procname)
{
    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);

    if (!_glfwPlatformGetCurrentContext())
    {
        _glfwInputError(GLFW_NO_CURRENT_CONTEXT, NULL);
        return NULL;
    }

    return _glfwPlatformGetProcAddress(procname);
}