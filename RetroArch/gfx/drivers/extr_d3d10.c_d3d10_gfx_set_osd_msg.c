#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
struct font_params {int dummy; } ;
struct TYPE_3__ {scalar_t__ enabled; } ;
struct TYPE_4__ {TYPE_1__ sprites; } ;
typedef  TYPE_2__ d3d10_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  font_driver_render_msg (int /*<<< orphan*/ *,void*,char const*,struct font_params const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void d3d10_gfx_set_osd_msg(
      void* data, video_frame_info_t* video_info, const char* msg, const void* params, void* font)
{
   d3d10_video_t* d3d10 = (d3d10_video_t*)data;

   if (d3d10)
   {
      if (d3d10->sprites.enabled)
         font_driver_render_msg(video_info, font, msg, (const struct font_params*)params);
      else
         printf("OSD msg: %s\n", msg);
   }
}