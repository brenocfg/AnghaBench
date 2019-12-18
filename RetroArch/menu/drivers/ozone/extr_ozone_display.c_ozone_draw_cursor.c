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
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_5__ {scalar_t__ has_all_assets; } ;
typedef  TYPE_1__ ozone_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ozone_draw_cursor_fallback (TYPE_1__*,int /*<<< orphan*/ *,int,unsigned int,unsigned int,size_t,float) ; 
 int /*<<< orphan*/  ozone_draw_cursor_slice (TYPE_1__*,int /*<<< orphan*/ *,int,unsigned int,unsigned int,size_t,float) ; 

void ozone_draw_cursor(ozone_handle_t *ozone,
      video_frame_info_t *video_info,
      int x_offset,
      unsigned width, unsigned height,
      size_t y, float alpha)
{
   if (ozone->has_all_assets)
      ozone_draw_cursor_slice(ozone, video_info, x_offset, width, height, y, alpha);
   else
      ozone_draw_cursor_fallback(ozone, video_info, x_offset, width, height, y, alpha);
}