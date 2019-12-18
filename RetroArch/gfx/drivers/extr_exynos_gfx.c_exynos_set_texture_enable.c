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
struct exynos_video {int menu_active; } ;

/* Variables and functions */

__attribute__((used)) static void exynos_set_texture_enable(void *data, bool state, bool full_screen)
{
   struct exynos_video *vid = data;
   if (vid)
      vid->menu_active = state;
}