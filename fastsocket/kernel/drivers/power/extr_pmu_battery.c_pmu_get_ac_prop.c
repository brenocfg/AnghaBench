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
union power_supply_propval {int intval; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int PMU_PWR_AC_PRESENT ; 
#define  POWER_SUPPLY_PROP_ONLINE 128 
 int /*<<< orphan*/  pmu_battery_count ; 
 int pmu_power_flags ; 

__attribute__((used)) static int pmu_get_ac_prop(struct power_supply *psy,
			   enum power_supply_property psp,
			   union power_supply_propval *val)
{
	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = (!!(pmu_power_flags & PMU_PWR_AC_PRESENT)) ||
			      (pmu_battery_count == 0);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}