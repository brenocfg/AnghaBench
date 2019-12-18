#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int menu_texture_enable; int should_resize; } ;
typedef  TYPE_1__ gx_video_t ;

/* Variables and functions */

__attribute__((used)) static void gx_set_texture_enable(void *data, bool enable, bool full_screen)
{
   gx_video_t *gx = (gx_video_t*)data;

   (void)full_screen;

   if (!gx)
      return;

   gx->menu_texture_enable = enable;
   /* need to make sure the game texture is the right pixel
    * format for menu overlay. */
   gx->should_resize = true;
}