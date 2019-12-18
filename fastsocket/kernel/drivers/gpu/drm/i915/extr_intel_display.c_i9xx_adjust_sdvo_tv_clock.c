#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_display_mode {int clock; } ;
struct TYPE_3__ {int p1; int p2; int n; int m1; int m2; } ;
typedef  TYPE_1__ intel_clock_t ;

/* Variables and functions */

__attribute__((used)) static void i9xx_adjust_sdvo_tv_clock(struct drm_display_mode *adjusted_mode,
				      intel_clock_t *clock)
{
	/* SDVO TV has fixed PLL values depend on its clock range,
	   this mirrors vbios setting. */
	if (adjusted_mode->clock >= 100000
	    && adjusted_mode->clock < 140500) {
		clock->p1 = 2;
		clock->p2 = 10;
		clock->n = 3;
		clock->m1 = 16;
		clock->m2 = 8;
	} else if (adjusted_mode->clock >= 140500
		   && adjusted_mode->clock <= 200000) {
		clock->p1 = 1;
		clock->p2 = 10;
		clock->n = 6;
		clock->m1 = 12;
		clock->m2 = 8;
	}
}