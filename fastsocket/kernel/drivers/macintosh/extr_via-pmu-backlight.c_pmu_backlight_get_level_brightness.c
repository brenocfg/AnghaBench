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

/* Variables and functions */
 int FB_BACKLIGHT_MAX ; 
 int MAX_PMU_LEVEL ; 
 int* bl_curve ; 

__attribute__((used)) static int pmu_backlight_get_level_brightness(int level)
{
	int pmulevel;

	/* Get and convert the value */
	pmulevel = bl_curve[level] * FB_BACKLIGHT_MAX / MAX_PMU_LEVEL;
	if (pmulevel < 0)
		pmulevel = 0;
	else if (pmulevel > MAX_PMU_LEVEL)
		pmulevel = MAX_PMU_LEVEL;

	return pmulevel;
}