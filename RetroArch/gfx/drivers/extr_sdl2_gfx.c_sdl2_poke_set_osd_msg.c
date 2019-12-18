#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  video_frame_info_t ;
typedef  int /*<<< orphan*/  sdl2_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,char const*) ; 
 int /*<<< orphan*/  sdl2_render_msg (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void sdl2_poke_set_osd_msg(void *data,
      video_frame_info_t *video_info,
      const char *msg,
      const void *params, void *font)
{
   sdl2_video_t *vid = (sdl2_video_t*)data;
   sdl2_render_msg(vid, msg);
   RARCH_LOG("[SDL2]: OSD MSG: %s\n", msg);
}