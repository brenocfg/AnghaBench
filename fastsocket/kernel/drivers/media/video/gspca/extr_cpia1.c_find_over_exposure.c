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
 int FLICKER_ALLOWABLE_OVER_EXPOSURE ; 
 int FLICKER_BRIGHTNESS_CONSTANT ; 
 int FLICKER_MAX_EXPOSURE ; 

__attribute__((used)) static int find_over_exposure(int brightness)
{
	int MaxAllowableOverExposure, OverExposure;

	MaxAllowableOverExposure = FLICKER_MAX_EXPOSURE - brightness -
				   FLICKER_BRIGHTNESS_CONSTANT;

	if (MaxAllowableOverExposure < FLICKER_ALLOWABLE_OVER_EXPOSURE)
		OverExposure = MaxAllowableOverExposure;
	else
		OverExposure = FLICKER_ALLOWABLE_OVER_EXPOSURE;

	return OverExposure;
}