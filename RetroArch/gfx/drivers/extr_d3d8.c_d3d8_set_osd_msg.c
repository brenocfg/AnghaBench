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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ d3d8_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  d3d8_begin_scene (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d8_end_scene (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  font_driver_render_msg (int /*<<< orphan*/ *,void*,char const*,void const*) ; 

__attribute__((used)) static void d3d8_set_osd_msg(void *data,
      video_frame_info_t *video_info,
      const char *msg,
      const void *params, void *font)
{
   d3d8_video_t          *d3d = (d3d8_video_t*)data;

   d3d8_begin_scene(d3d->dev);
   font_driver_render_msg(video_info, font, msg, params);
   d3d8_end_scene(d3d->dev);
}