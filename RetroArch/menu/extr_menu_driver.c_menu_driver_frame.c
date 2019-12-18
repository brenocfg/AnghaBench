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
struct TYPE_5__ {scalar_t__ menu_is_alive; } ;
typedef  TYPE_1__ video_frame_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* frame ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;

/* Variables and functions */
 TYPE_4__* menu_driver_ctx ; 
 int /*<<< orphan*/  menu_userdata ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

void menu_driver_frame(video_frame_info_t *video_info)
{
   if (video_info->menu_is_alive && menu_driver_ctx->frame)
      menu_driver_ctx->frame(menu_userdata, video_info);
}