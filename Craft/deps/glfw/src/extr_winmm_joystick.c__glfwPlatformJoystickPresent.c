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
typedef  int /*<<< orphan*/  JOYINFO ;

/* Variables and functions */
 int GL_FALSE ; 
 int GL_TRUE ; 
 scalar_t__ JOYERR_NOERROR ; 
 scalar_t__ _glfw_joyGetPos (int,int /*<<< orphan*/ *) ; 

int _glfwPlatformJoystickPresent(int joy)
{
    JOYINFO ji;

    if (_glfw_joyGetPos(joy, &ji) != JOYERR_NOERROR)
        return GL_FALSE;

    return GL_TRUE;
}