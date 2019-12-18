#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct TYPE_5__ {scalar_t__ height; scalar_t__ width; } ;
typedef  TYPE_1__ menu_display_ctx_draw_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* draw ) (TYPE_1__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_4__* menu_disp ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 

void menu_display_draw(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
   if (!menu_disp || !draw || !menu_disp->draw)
      return;

   if (draw->height <= 0)
      return;
   if (draw->width <= 0)
      return;
   menu_disp->draw(draw, video_info);
}