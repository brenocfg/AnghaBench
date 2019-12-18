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
union power_supply_propval {void* intval; } ;
typedef  int uint8_t ;
struct TYPE_2__ {int ecver; } ;

/* Variables and functions */
 int BAT_STAT_AC ; 
 int BAT_STAT_CHARGING ; 
 int BAT_STAT_DISCHARGING ; 
 int BAT_STAT_FULL ; 
 int BAT_STAT_TRICKLE ; 
 void* POWER_SUPPLY_STATUS_CHARGING ; 
 void* POWER_SUPPLY_STATUS_DISCHARGING ; 
 void* POWER_SUPPLY_STATUS_FULL ; 
 void* POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 TYPE_1__ olpc_platform_info ; 

__attribute__((used)) static int olpc_bat_get_status(union power_supply_propval *val, uint8_t ec_byte)
{
	if (olpc_platform_info.ecver > 0x44) {
		if (ec_byte & (BAT_STAT_CHARGING | BAT_STAT_TRICKLE))
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else if (ec_byte & BAT_STAT_DISCHARGING)
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		else if (ec_byte & BAT_STAT_FULL)
			val->intval = POWER_SUPPLY_STATUS_FULL;
		else /* er,... */
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
	} else {
		/* Older EC didn't report charge/discharge bits */
		if (!(ec_byte & BAT_STAT_AC)) /* No AC means discharging */
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		else if (ec_byte & BAT_STAT_FULL)
			val->intval = POWER_SUPPLY_STATUS_FULL;
		else /* Not _necessarily_ true but EC doesn't tell all yet */
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
	}

	return 0;
}