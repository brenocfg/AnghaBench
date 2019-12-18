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
union power_supply_propval {scalar_t__ intval; } ;
struct apm_power_info {int battery_life; int time; int /*<<< orphan*/  units; int /*<<< orphan*/  battery_status; int /*<<< orphan*/  battery_flag; int /*<<< orphan*/  ac_line_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  APM_AC_OFFLINE ; 
 int /*<<< orphan*/  APM_AC_ONLINE ; 
 int /*<<< orphan*/  APM_BATTERY_STATUS_CHARGING ; 
 int /*<<< orphan*/  APM_BATTERY_STATUS_CRITICAL ; 
 int /*<<< orphan*/  APM_BATTERY_STATUS_HIGH ; 
 int /*<<< orphan*/  APM_BATTERY_STATUS_LOW ; 
 int /*<<< orphan*/  APM_UNITS_MINS ; 
 int /*<<< orphan*/  CAPACITY ; 
 scalar_t__ MPSY_PROP (int /*<<< orphan*/ ,union power_supply_propval*) ; 
 scalar_t__ POWER_SUPPLY_STATUS_CHARGING ; 
 scalar_t__ POWER_SUPPLY_STATUS_FULL ; 
 scalar_t__ POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 scalar_t__ POWER_SUPPLY_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  SOURCE_CHARGE ; 
 int /*<<< orphan*/  SOURCE_ENERGY ; 
 int /*<<< orphan*/  SOURCE_VOLTAGE ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  TIME_TO_EMPTY_AVG ; 
 int /*<<< orphan*/  TIME_TO_EMPTY_NOW ; 
 int /*<<< orphan*/  TIME_TO_FULL_AVG ; 
 int /*<<< orphan*/  TIME_TO_FULL_NOW ; 
 int /*<<< orphan*/  apm_mutex ; 
 void* calculate_capacity (int /*<<< orphan*/ ) ; 
 void* calculate_time (int) ; 
 int /*<<< orphan*/  find_main_battery () ; 
 int /*<<< orphan*/  main_battery ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void apm_battery_apm_get_power_status(struct apm_power_info *info)
{
	union power_supply_propval status;
	union power_supply_propval capacity, time_to_full, time_to_empty;

	mutex_lock(&apm_mutex);
	find_main_battery();
	if (!main_battery) {
		mutex_unlock(&apm_mutex);
		return;
	}

	/* status */

	if (MPSY_PROP(STATUS, &status))
		status.intval = POWER_SUPPLY_STATUS_UNKNOWN;

	/* ac line status */

	if ((status.intval == POWER_SUPPLY_STATUS_CHARGING) ||
	    (status.intval == POWER_SUPPLY_STATUS_NOT_CHARGING) ||
	    (status.intval == POWER_SUPPLY_STATUS_FULL))
		info->ac_line_status = APM_AC_ONLINE;
	else
		info->ac_line_status = APM_AC_OFFLINE;

	/* battery life (i.e. capacity, in percents) */

	if (MPSY_PROP(CAPACITY, &capacity) == 0) {
		info->battery_life = capacity.intval;
	} else {
		/* try calculate using energy */
		info->battery_life = calculate_capacity(SOURCE_ENERGY);
		/* if failed try calculate using charge instead */
		if (info->battery_life == -1)
			info->battery_life = calculate_capacity(SOURCE_CHARGE);
		if (info->battery_life == -1)
			info->battery_life = calculate_capacity(SOURCE_VOLTAGE);
	}

	/* charging status */

	if (status.intval == POWER_SUPPLY_STATUS_CHARGING) {
		info->battery_status = APM_BATTERY_STATUS_CHARGING;
	} else {
		if (info->battery_life > 50)
			info->battery_status = APM_BATTERY_STATUS_HIGH;
		else if (info->battery_life > 5)
			info->battery_status = APM_BATTERY_STATUS_LOW;
		else
			info->battery_status = APM_BATTERY_STATUS_CRITICAL;
	}
	info->battery_flag = info->battery_status;

	/* time */

	info->units = APM_UNITS_MINS;

	if (status.intval == POWER_SUPPLY_STATUS_CHARGING) {
		if (!MPSY_PROP(TIME_TO_FULL_AVG, &time_to_full) ||
				!MPSY_PROP(TIME_TO_FULL_NOW, &time_to_full))
			info->time = time_to_full.intval / 60;
		else
			info->time = calculate_time(status.intval);
	} else {
		if (!MPSY_PROP(TIME_TO_EMPTY_AVG, &time_to_empty) ||
			      !MPSY_PROP(TIME_TO_EMPTY_NOW, &time_to_empty))
			info->time = time_to_empty.intval / 60;
		else
			info->time = calculate_time(status.intval);
	}

	mutex_unlock(&apm_mutex);
}