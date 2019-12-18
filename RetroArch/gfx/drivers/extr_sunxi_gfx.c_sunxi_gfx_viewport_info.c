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
struct video_viewport {int /*<<< orphan*/  full_height; int /*<<< orphan*/  height; int /*<<< orphan*/  full_width; int /*<<< orphan*/  width; scalar_t__ y; scalar_t__ x; } ;
struct sunxi_video {int /*<<< orphan*/  src_height; int /*<<< orphan*/  src_width; } ;

/* Variables and functions */

__attribute__((used)) static void sunxi_gfx_viewport_info(void *data, struct video_viewport *vp)
{
   struct sunxi_video *_dispvars = (struct sunxi_video*)data;

   if (!vp || !_dispvars)
      return;

   vp->x = vp->y = 0;

   vp->width  = vp->full_width  = _dispvars->src_width;
   vp->height = vp->full_height = _dispvars->src_height;
}