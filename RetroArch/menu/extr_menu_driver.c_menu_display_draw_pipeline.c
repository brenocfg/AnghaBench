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
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  int /*<<< orphan*/  menu_display_ctx_draw_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* draw_pipeline ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* menu_disp ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void menu_display_draw_pipeline(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
   if (menu_disp && draw && menu_disp->draw_pipeline)
      menu_disp->draw_pipeline(draw, video_info);
}