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
typedef  int uint8_t ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int BAT_STAT_AC ; 
 int /*<<< orphan*/  EC_BAT_STATUS ; 
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_ONLINE 128 
 int olpc_ec_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int olpc_ac_get_prop(struct power_supply *psy,
			    enum power_supply_property psp,
			    union power_supply_propval *val)
{
	int ret = 0;
	uint8_t status;

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		ret = olpc_ec_cmd(EC_BAT_STATUS, NULL, 0, &status, 1);
		if (ret)
			return ret;

		val->intval = !!(status & BAT_STAT_AC);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}