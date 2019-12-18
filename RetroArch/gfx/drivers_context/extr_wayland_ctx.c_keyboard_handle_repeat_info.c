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
struct wl_keyboard {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */

void keyboard_handle_repeat_info(void *data,
      struct wl_keyboard *wl_keyboard,
      int32_t rate,
      int32_t delay)
{
   (void)data;
   (void)wl_keyboard;
   (void)rate;
   (void)delay;
   /* TODO: Seems like we'll need this to get
    * repeat working. We'll have to do it on our own. */
}