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
struct exynos_video {unsigned int menu_rotation; } ;

/* Variables and functions */

__attribute__((used)) static void exynos_gfx_set_rotation(void *data, unsigned rotation)
{
   struct exynos_video *vid = (struct exynos_video*)data;
   if (vid)
      vid->menu_rotation = rotation;
}