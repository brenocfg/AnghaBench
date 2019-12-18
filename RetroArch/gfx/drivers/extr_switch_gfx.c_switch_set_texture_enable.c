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
struct TYPE_3__ {int enable; int fullscreen; } ;
struct TYPE_4__ {TYPE_1__ menu_texture; } ;
typedef  TYPE_2__ switch_video_t ;

/* Variables and functions */

__attribute__((used)) static void switch_set_texture_enable(void *data, bool enable, bool full_screen)
{
	switch_video_t *sw = data;
   if (!sw)
      return;

	sw->menu_texture.enable = enable;
	sw->menu_texture.fullscreen = full_screen;
}