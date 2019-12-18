#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ video_frame_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  menu_display_draw_quad (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_display_set_alpha (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  ozone_backdrop ; 

void ozone_draw_backdrop(video_frame_info_t *video_info, float alpha)
{
   /* TODO: Replace this backdrop by a blur shader on the whole screen if available */
   menu_display_set_alpha(ozone_backdrop, alpha);
   menu_display_draw_quad(video_info, 0, 0, video_info->width, video_info->height, video_info->width, video_info->height, ozone_backdrop);
}