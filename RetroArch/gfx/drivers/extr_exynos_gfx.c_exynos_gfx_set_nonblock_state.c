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
struct exynos_video {TYPE_1__* data; } ;
struct TYPE_2__ {int sync; } ;

/* Variables and functions */

__attribute__((used)) static void exynos_gfx_set_nonblock_state(void *data, bool state)
{
   struct exynos_video *vid = data;
   if (vid && vid->data)
      vid->data->sync = !state;
}