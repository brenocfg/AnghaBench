#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wl_seat {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * wl_touch; int /*<<< orphan*/ * wl_pointer; int /*<<< orphan*/ * wl_keyboard; } ;
typedef  TYPE_1__ gfx_ctx_wayland_data_t ;

/* Variables and functions */
 unsigned int WL_SEAT_CAPABILITY_KEYBOARD ; 
 unsigned int WL_SEAT_CAPABILITY_POINTER ; 
 unsigned int WL_SEAT_CAPABILITY_TOUCH ; 
 int /*<<< orphan*/  keyboard_listener ; 
 int /*<<< orphan*/  pointer_listener ; 
 int /*<<< orphan*/  touch_listener ; 
 int /*<<< orphan*/  wl_keyboard_add_listener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  wl_keyboard_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_pointer_add_listener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  wl_pointer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wl_seat_get_keyboard (struct wl_seat*) ; 
 int /*<<< orphan*/ * wl_seat_get_pointer (struct wl_seat*) ; 
 int /*<<< orphan*/ * wl_seat_get_touch (struct wl_seat*) ; 
 int /*<<< orphan*/  wl_touch_add_listener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  wl_touch_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void seat_handle_capabilities(void *data,
      struct wl_seat *seat, unsigned caps)
{
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;

   if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && !wl->wl_keyboard)
   {
      wl->wl_keyboard = wl_seat_get_keyboard(seat);
      wl_keyboard_add_listener(wl->wl_keyboard, &keyboard_listener, wl);
   }
   else if (!(caps & WL_SEAT_CAPABILITY_KEYBOARD) && wl->wl_keyboard)
   {
      wl_keyboard_destroy(wl->wl_keyboard);
      wl->wl_keyboard = NULL;
   }
   if ((caps & WL_SEAT_CAPABILITY_POINTER) && !wl->wl_pointer)
   {
      wl->wl_pointer = wl_seat_get_pointer(seat);
      wl_pointer_add_listener(wl->wl_pointer, &pointer_listener, wl);
   }
   else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && wl->wl_pointer)
   {
      wl_pointer_destroy(wl->wl_pointer);
      wl->wl_pointer = NULL;
   }
   if ((caps & WL_SEAT_CAPABILITY_TOUCH) && !wl->wl_touch)
   {
      wl->wl_touch = wl_seat_get_touch(seat);
      wl_touch_add_listener(wl->wl_touch, &touch_listener, wl);
   }
   else if (!(caps & WL_SEAT_CAPABILITY_TOUCH) && wl->wl_touch)
   {
      wl_touch_destroy(wl->wl_touch);
      wl->wl_touch = NULL;
   }

}