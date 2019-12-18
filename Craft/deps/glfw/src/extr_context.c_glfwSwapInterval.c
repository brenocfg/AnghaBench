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

/* Variables and functions */
 int /*<<< orphan*/  GLFW_NO_CURRENT_CONTEXT ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwPlatformGetCurrentContext () ; 
 int /*<<< orphan*/  _glfwPlatformSwapInterval (int) ; 

void glfwSwapInterval(int interval)
{
    _GLFW_REQUIRE_INIT();

    if (!_glfwPlatformGetCurrentContext())
    {
        _glfwInputError(GLFW_NO_CURRENT_CONTEXT, NULL);
        return;
    }

    _glfwPlatformSwapInterval(interval);
}