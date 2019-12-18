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
struct wl_seat {int dummy; } ;
typedef  enum wl_seat_capability { ____Placeholder_wl_seat_capability } wl_seat_capability ;
struct TYPE_3__ {int /*<<< orphan*/ * keyboard; int /*<<< orphan*/ * pointer; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 int WL_SEAT_CAPABILITY_KEYBOARD ; 
 int WL_SEAT_CAPABILITY_POINTER ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  keyboardListener ; 
 int /*<<< orphan*/  pointerListener ; 
 int /*<<< orphan*/  wl_keyboard_add_listener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_keyboard_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_pointer_add_listener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_pointer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wl_seat_get_keyboard (struct wl_seat*) ; 
 int /*<<< orphan*/ * wl_seat_get_pointer (struct wl_seat*) ; 

__attribute__((used)) static void seatHandleCapabilities(void* data,
                                   struct wl_seat* seat,
                                   enum wl_seat_capability caps)
{
    if ((caps & WL_SEAT_CAPABILITY_POINTER) && !_glfw.wl.pointer)
    {
        _glfw.wl.pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(_glfw.wl.pointer, &pointerListener, NULL);
    }
    else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && _glfw.wl.pointer)
    {
        wl_pointer_destroy(_glfw.wl.pointer);
        _glfw.wl.pointer = NULL;
    }

    if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && !_glfw.wl.keyboard)
    {
        _glfw.wl.keyboard = wl_seat_get_keyboard(seat);
        wl_keyboard_add_listener(_glfw.wl.keyboard, &keyboardListener, NULL);
    }
    else if (!(caps & WL_SEAT_CAPABILITY_KEYBOARD) && _glfw.wl.keyboard)
    {
        wl_keyboard_destroy(_glfw.wl.keyboard);
        _glfw.wl.keyboard = NULL;
    }
}