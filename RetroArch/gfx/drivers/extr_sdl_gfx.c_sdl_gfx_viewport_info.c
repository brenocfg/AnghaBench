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
struct video_viewport {int /*<<< orphan*/  full_height; int /*<<< orphan*/  height; int /*<<< orphan*/  full_width; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_4__ {TYPE_1__* screen; } ;
typedef  TYPE_2__ sdl_video_t ;
struct TYPE_3__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;

/* Variables and functions */

__attribute__((used)) static void sdl_gfx_viewport_info(void *data, struct video_viewport *vp)
{
   sdl_video_t *vid = (sdl_video_t*)data;
   vp->x      = 0;
   vp->y      = 0;
   vp->width  = vp->full_width  = vid->screen->w;
   vp->height = vp->full_height = vid->screen->h;
}