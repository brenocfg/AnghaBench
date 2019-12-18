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
struct video_viewport {int x; int width; int y; int height; scalar_t__ full_height; scalar_t__ full_width; } ;
struct TYPE_2__ {int x; int y; } ;

/* Variables and functions */
 TYPE_1__* g_mice ; 
 unsigned int g_mouse_cnt ; 
 int g_mouse_xy_mapping_ready ; 
 double g_view_abs_ratio_x ; 
 double g_view_abs_ratio_y ; 
 scalar_t__ video_driver_get_viewport_info (struct video_viewport*) ; 

__attribute__((used)) static void winraw_init_mouse_xy_mapping(void)
{
   struct video_viewport viewport;
   int center_x;
   int center_y;
   unsigned i;

   if (video_driver_get_viewport_info(&viewport))
   {
      center_x = viewport.x + viewport.width / 2;
      center_y = viewport.y + viewport.height / 2;

      for (i = 0; i < g_mouse_cnt; ++i)
      {
         g_mice[i].x = center_x;
         g_mice[i].y = center_y;
      }

      g_view_abs_ratio_x = (double)viewport.full_width / 65535.0;
      g_view_abs_ratio_y = (double)viewport.full_height / 65535.0;

      g_mouse_xy_mapping_ready = true;
   }
}