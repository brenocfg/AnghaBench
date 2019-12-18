#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct font_params {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ d3d9_video_t ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE9 ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_begin_scene (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_end_scene (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_set_font_rect (TYPE_1__*,struct font_params const*) ; 
 int /*<<< orphan*/  font_driver_render_msg (int /*<<< orphan*/ *,void*,char const*,struct font_params const*) ; 

__attribute__((used)) static void d3d9_set_osd_msg(void *data,
      video_frame_info_t *video_info,
      const char *msg,
      const void *params, void *font)
{
   d3d9_video_t          *d3d = (d3d9_video_t*)data;
   LPDIRECT3DDEVICE9     dev  = d3d->dev;
   const struct font_params *d3d_font_params = (const
         struct font_params*)params;

   d3d9_set_font_rect(d3d, d3d_font_params);
   d3d9_begin_scene(dev);
   font_driver_render_msg(video_info, font,
         msg, d3d_font_params);
   d3d9_end_scene(dev);
}