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
struct radeon_bl_privdata {scalar_t__ negative; TYPE_2__* rinfo; } ;
struct TYPE_4__ {TYPE_1__* info; } ;
struct TYPE_3__ {int* bl_curve; } ;

/* Variables and functions */
 int FB_BACKLIGHT_MAX ; 
 int MAX_RADEON_LEVEL ; 

__attribute__((used)) static int radeon_bl_get_level_brightness(struct radeon_bl_privdata *pdata,
		int level)
{
	int rlevel;

	/* Get and convert the value */
	/* No locking of bl_curve since we read a single value */
	rlevel = pdata->rinfo->info->bl_curve[level] *
		 FB_BACKLIGHT_MAX / MAX_RADEON_LEVEL;

	if (rlevel < 0)
		rlevel = 0;
	else if (rlevel > MAX_RADEON_LEVEL)
		rlevel = MAX_RADEON_LEVEL;

	if (pdata->negative)
		rlevel = MAX_RADEON_LEVEL - rlevel;

	return rlevel;
}