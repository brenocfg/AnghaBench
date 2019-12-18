#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_surface {int dummy; } ;
struct wl_pointer {int dummy; } ;
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_3__ {int /*<<< orphan*/ * pointerFocus; int /*<<< orphan*/  pointerSerial; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FALSE ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputCursorEnter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pointerHandleLeave(void* data,
                               struct wl_pointer* pointer,
                               uint32_t serial,
                               struct wl_surface* surface)
{
    _GLFWwindow* window = _glfw.wl.pointerFocus;

    if (!window)
        return;

    _glfw.wl.pointerSerial = serial;
    _glfw.wl.pointerFocus = NULL;
    _glfwInputCursorEnter(window, GL_FALSE);
}