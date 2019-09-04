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
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int uint32_t ;
struct wl_pointer {int dummy; } ;
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_3__ {int /*<<< orphan*/ * pointerFocus; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
#define  WL_POINTER_AXIS_HORIZONTAL_SCROLL 129 
#define  WL_POINTER_AXIS_VERTICAL_SCROLL 128 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputScroll (int /*<<< orphan*/ *,double,double) ; 
 double wl_fixed_to_double (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pointerHandleAxis(void* data,
                              struct wl_pointer* wl_pointer,
                              uint32_t time,
                              uint32_t axis,
                              wl_fixed_t value)
{
    _GLFWwindow* window = _glfw.wl.pointerFocus;
    double scroll_factor;
    double x, y;

    if (!window)
        return;

    /* Wayland scroll events are in pointer motion coordinate space (think
     * two finger scroll). The factor 10 is commonly used to convert to
     * "scroll step means 1.0. */
    scroll_factor = 1.0/10.0;

    switch (axis)
    {
        case WL_POINTER_AXIS_HORIZONTAL_SCROLL:
            x = wl_fixed_to_double(value) * scroll_factor;
            y = 0.0;
            break;
        case WL_POINTER_AXIS_VERTICAL_SCROLL:
            x = 0.0;
            y = wl_fixed_to_double(value) * scroll_factor;
            break;
        default:
            break;
    }

    _glfwInputScroll(window, x, y);
}