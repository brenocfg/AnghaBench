#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* js; } ;
struct TYPE_6__ {TYPE_2__ linux_js; } ;
struct TYPE_4__ {int buttonCount; unsigned char const* buttons; } ;

/* Variables and functions */
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  pollJoystickEvents () ; 

const unsigned char* _glfwPlatformGetJoystickButtons(int joy, int* count)
{
    pollJoystickEvents();

    *count = _glfw.linux_js.js[joy].buttonCount;
    return _glfw.linux_js.js[joy].buttons;
}