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
typedef  scalar_t__ uint32_t ;
struct wl_pointer {int dummy; } ;
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_4__ {int /*<<< orphan*/  modifiers; } ;
struct TYPE_5__ {TYPE_1__ xkb; int /*<<< orphan*/ * pointerFocus; } ;
struct TYPE_6__ {TYPE_2__ wl; } ;

/* Variables and functions */
 scalar_t__ BTN_LEFT ; 
 int /*<<< orphan*/  GLFW_PRESS ; 
 int /*<<< orphan*/  GLFW_RELEASE ; 
 scalar_t__ WL_POINTER_BUTTON_STATE_PRESSED ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  _glfwInputMouseClick (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pointerHandleButton(void* data,
                                struct wl_pointer* wl_pointer,
                                uint32_t serial,
                                uint32_t time,
                                uint32_t button,
                                uint32_t state)
{
    _GLFWwindow* window = _glfw.wl.pointerFocus;
    int glfwButton;

    if (!window)
        return;

    /* Makes left, right and middle 0, 1 and 2. Overall order follows evdev
     * codes. */
    glfwButton = button - BTN_LEFT;

    _glfwInputMouseClick(window,
                         glfwButton,
                         state == WL_POINTER_BUTTON_STATE_PRESSED
                                ? GLFW_PRESS
                                : GLFW_RELEASE,
                         _glfw.wl.xkb.modifiers);
}