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
struct TYPE_3__ {int enabled; int fullscreen; } ;
struct TYPE_4__ {TYPE_1__ menu; } ;
typedef  TYPE_2__ d3d10_video_t ;

/* Variables and functions */

__attribute__((used)) static void d3d10_set_menu_texture_enable(void* data, bool state, bool full_screen)
{
   d3d10_video_t* d3d10 = (d3d10_video_t*)data;

   if (!d3d10)
      return;

   d3d10->menu.enabled    = state;
   d3d10->menu.fullscreen = full_screen;
}