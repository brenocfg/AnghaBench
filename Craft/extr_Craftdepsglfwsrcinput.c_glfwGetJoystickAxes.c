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
 int /*<<< orphan*/  GLFW_INVALID_ENUM ; 
 int GLFW_JOYSTICK_LAST ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 float const* _glfwPlatformGetJoystickAxes (int,int*) ; 

const float* glfwGetJoystickAxes(int joy, int* count)
{
    *count = 0;

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);

    if (joy < 0 || joy > GLFW_JOYSTICK_LAST)
    {
        _glfwInputError(GLFW_INVALID_ENUM, "Invalid joystick");
        return NULL;
    }

    return _glfwPlatformGetJoystickAxes(joy, count);
}