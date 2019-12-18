#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ userdata; } ;
typedef  TYPE_1__ video_frame_info_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ d3d9_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_enable_blend_func (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void menu_display_d3d9_blend_begin(video_frame_info_t *video_info)
{
   d3d9_video_t *d3d = (d3d9_video_t*)video_info->userdata;

   if (!d3d)
      return;

   d3d9_enable_blend_func(d3d->dev);
}