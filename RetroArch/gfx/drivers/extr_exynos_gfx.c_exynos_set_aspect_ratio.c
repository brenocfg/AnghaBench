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
struct exynos_video {int aspect_changed; } ;

/* Variables and functions */

__attribute__((used)) static void exynos_set_aspect_ratio(void *data, unsigned aspect_ratio_idx)
{
   struct exynos_video *vid = (struct exynos_video*)data;

   if (!vid)
      return;

   vid->aspect_changed = true;
}