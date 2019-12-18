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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct ds2760_device_info {int /*<<< orphan*/  rem_capacity; int /*<<< orphan*/  life_sec; int /*<<< orphan*/  temp_C; int /*<<< orphan*/  accum_current_uAh; int /*<<< orphan*/  empty_uAh; int /*<<< orphan*/  full_active_uAh; int /*<<< orphan*/  rated_capacity; int /*<<< orphan*/  current_uA; int /*<<< orphan*/  voltage_uV; int /*<<< orphan*/  charge_status; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY 137 
#define  POWER_SUPPLY_PROP_CHARGE_EMPTY 136 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 135 
#define  POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN 134 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 133 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 132 
#define  POWER_SUPPLY_PROP_STATUS 131 
#define  POWER_SUPPLY_PROP_TEMP 130 
#define  POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int /*<<< orphan*/  ds2760_battery_read_status (struct ds2760_device_info*) ; 
 struct ds2760_device_info* to_ds2760_device_info (struct power_supply*) ; 

__attribute__((used)) static int ds2760_battery_get_property(struct power_supply *psy,
				       enum power_supply_property psp,
				       union power_supply_propval *val)
{
	struct ds2760_device_info *di = to_ds2760_device_info(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = di->charge_status;
		return 0;
	default:
		break;
	}

	ds2760_battery_read_status(di);

	switch (psp) {
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = di->voltage_uV;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		val->intval = di->current_uA;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->intval = di->rated_capacity;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		val->intval = di->full_active_uAh;
		break;
	case POWER_SUPPLY_PROP_CHARGE_EMPTY:
		val->intval = di->empty_uAh;
		break;
	case POWER_SUPPLY_PROP_CHARGE_NOW:
		val->intval = di->accum_current_uAh;
		break;
	case POWER_SUPPLY_PROP_TEMP:
		val->intval = di->temp_C;
		break;
	case POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW:
		val->intval = di->life_sec;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = di->rem_capacity;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}