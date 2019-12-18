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
struct exynos_video {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */

__attribute__((used)) static void exynos_gfx_viewport_info(void *data, struct video_viewport *vp)
{
   struct exynos_video *vid = (struct exynos_video*)data;

   if (!vid)
      return;

   vp->x = vp->y = 0;

   vp->width  = vp->full_width  = vid->width;
   vp->height = vp->full_height = vid->height;
}