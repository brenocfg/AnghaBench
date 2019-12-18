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
 scalar_t__ menu_animation_is_active () ; 
 scalar_t__ menu_display_framebuf_dirty ; 

bool menu_display_get_update_pending(void)
{
   if (menu_animation_is_active() || menu_display_framebuf_dirty)
      return true;
   return false;
}