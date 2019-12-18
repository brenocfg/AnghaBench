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
struct TYPE_4__ {int vsync; } ;
struct TYPE_5__ {TYPE_1__ video; } ;
typedef  TYPE_2__ sdl2_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  sdl_refresh_renderer (TYPE_2__*) ; 

__attribute__((used)) static void sdl2_gfx_set_nonblock_state(void *data, bool toggle)
{
   sdl2_video_t *vid = (sdl2_video_t*)data;

   vid->video.vsync = !toggle;
   sdl_refresh_renderer(vid);
}