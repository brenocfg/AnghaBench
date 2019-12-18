#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ complete; } ;

/* Variables and functions */
 int LEVEL_TO_BRIGHT (int) ; 
 int /*<<< orphan*/  PMU_BACKLIGHT_BRIGHT ; 
 int /*<<< orphan*/  PMU_POWER_CTRL ; 
 int PMU_POW_BACKLIGHT ; 
 int PMU_POW_OFF ; 
 int PMU_POW_ON ; 
 int /*<<< orphan*/  backlight_enabled ; 
 int backlight_level ; 
 TYPE_1__ bright_req_1 ; 
 TYPE_1__ bright_req_2 ; 
 int /*<<< orphan*/  pmu_request (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void 
pmu_set_brightness(int level)
{
	int bright;

	backlight_level = level;
	bright = LEVEL_TO_BRIGHT(level);
	if (!backlight_enabled)
		return;
	if (bright_req_1.complete)
		pmu_request(&bright_req_1, NULL, 2, PMU_BACKLIGHT_BRIGHT,
		    bright);
	if (bright_req_2.complete)
		pmu_request(&bright_req_2, NULL, 2, PMU_POWER_CTRL,
		    PMU_POW_BACKLIGHT | (bright < 0x7f ? PMU_POW_ON : PMU_POW_OFF));
}