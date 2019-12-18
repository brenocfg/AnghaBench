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
struct da9030_charger {int fault; } ;

/* Variables and functions */
 int DA9030_FAULT_LOG_OVER_TEMP ; 
 int DA9030_FAULT_LOG_VBAT_OVER ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_GOOD ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 

__attribute__((used)) static void da9030_battery_check_health(struct da9030_charger *charger,
				    union power_supply_propval *val)
{
	if (charger->fault & DA9030_FAULT_LOG_OVER_TEMP)
		val->intval = POWER_SUPPLY_HEALTH_OVERHEAT;
	else if (charger->fault & DA9030_FAULT_LOG_VBAT_OVER)
		val->intval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	else
		val->intval = POWER_SUPPLY_HEALTH_GOOD;
}