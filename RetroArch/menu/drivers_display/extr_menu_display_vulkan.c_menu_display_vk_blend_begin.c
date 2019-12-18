#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int blend; } ;
struct TYPE_6__ {TYPE_1__ display; } ;
typedef  TYPE_2__ vk_t ;
struct TYPE_7__ {scalar_t__ userdata; } ;
typedef  TYPE_3__ video_frame_info_t ;

/* Variables and functions */

__attribute__((used)) static void menu_display_vk_blend_begin(video_frame_info_t *video_info)
{
   vk_t *vk = (vk_t*)video_info->userdata;

   if (vk)
      vk->display.blend = true;
}