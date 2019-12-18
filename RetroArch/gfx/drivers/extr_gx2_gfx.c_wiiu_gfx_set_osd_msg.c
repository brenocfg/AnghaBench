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
struct TYPE_2__ {scalar_t__ render_msg_enabled; } ;
typedef  TYPE_1__ wiiu_video_t ;
typedef  int /*<<< orphan*/  video_frame_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  font_driver_render_msg (int /*<<< orphan*/ *,void*,char const*,void const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static void wiiu_gfx_set_osd_msg(void *data,
                                 video_frame_info_t *video_info,
                                 const char *msg,
                                 const void *params, void *font)
{
   wiiu_video_t *wiiu = (wiiu_video_t *)data;

   if (wiiu)
   {
      if (wiiu->render_msg_enabled)
         font_driver_render_msg(video_info, font, msg, params);
      else
         printf("OSD msg: %s\n", msg);
   }

}