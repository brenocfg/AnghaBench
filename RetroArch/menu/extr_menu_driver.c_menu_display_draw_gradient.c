#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  menu_wallpaper_opacity; } ;
typedef  TYPE_1__ video_frame_info_t ;
struct TYPE_10__ {scalar_t__ y; scalar_t__ x; scalar_t__ texture; } ;
typedef  TYPE_2__ menu_display_ctx_draw_t ;

/* Variables and functions */
 int /*<<< orphan*/  menu_display_draw (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  menu_display_draw_bg (TYPE_2__*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

void menu_display_draw_gradient(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
   draw->texture       = 0;
   draw->x             = 0;
   draw->y             = 0;

   menu_display_draw_bg(draw, video_info, false,
         video_info->menu_wallpaper_opacity);
   menu_display_draw(draw, video_info);
}