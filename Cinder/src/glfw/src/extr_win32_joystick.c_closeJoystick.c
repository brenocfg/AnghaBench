#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  objects; int /*<<< orphan*/  buttons; int /*<<< orphan*/  axes; int /*<<< orphan*/  name; scalar_t__ device; } ;
typedef  TYPE_1__ _GLFWjoystickWin32 ;
struct TYPE_6__ {TYPE_1__* win32_js; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_DISCONNECTED ; 
 int /*<<< orphan*/  IDirectInputDevice8_Release (scalar_t__) ; 
 int /*<<< orphan*/  IDirectInputDevice8_Unacquire (scalar_t__) ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfwInputJoystickChange (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void closeJoystick(_GLFWjoystickWin32* js)
{
    if (js->device)
    {
        IDirectInputDevice8_Unacquire(js->device);
        IDirectInputDevice8_Release(js->device);
    }

    free(js->name);
    free(js->axes);
    free(js->buttons);
    free(js->objects);
    memset(js, 0, sizeof(_GLFWjoystickWin32));

    _glfwInputJoystickChange((int) (js - _glfw.win32_js), GLFW_DISCONNECTED);
}