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
struct TYPE_3__ {int force_aspect; } ;
struct TYPE_4__ {int should_resize; TYPE_1__ video; } ;
typedef  TYPE_2__ sdl2_video_t ;

/* Variables and functions */

__attribute__((used)) static void sdl2_poke_set_aspect_ratio(void *data, unsigned aspect_ratio_idx)
{
   sdl2_video_t *vid    = (sdl2_video_t*)data;

   /* FIXME: Why is vid NULL here when starting content? */
   if (!vid)
      return;

   vid->video.force_aspect = true;
   vid->should_resize      = true;
}