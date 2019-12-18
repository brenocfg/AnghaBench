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
typedef  int uint8_t ;

/* Variables and functions */
#define  BAT_ERR_ACR_FAIL 133 
#define  BAT_ERR_ID_FAIL 132 
#define  BAT_ERR_INFOFAIL 131 
#define  BAT_ERR_OUT_OF_CONTROL 130 
#define  BAT_ERR_OVERTEMP 129 
#define  BAT_ERR_OVERVOLTAGE 128 
 int /*<<< orphan*/  EC_BAT_ERRCODE ; 
 int EIO ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_GOOD ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
 int olpc_ec_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int olpc_bat_get_health(union power_supply_propval *val)
{
	uint8_t ec_byte;
	int ret;

	ret = olpc_ec_cmd(EC_BAT_ERRCODE, NULL, 0, &ec_byte, 1);
	if (ret)
		return ret;

	switch (ec_byte) {
	case 0:
		val->intval = POWER_SUPPLY_HEALTH_GOOD;
		break;

	case BAT_ERR_OVERTEMP:
		val->intval = POWER_SUPPLY_HEALTH_OVERHEAT;
		break;

	case BAT_ERR_OVERVOLTAGE:
		val->intval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		break;

	case BAT_ERR_INFOFAIL:
	case BAT_ERR_OUT_OF_CONTROL:
	case BAT_ERR_ID_FAIL:
	case BAT_ERR_ACR_FAIL:
		val->intval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		break;

	default:
		/* Eep. We don't know this failure code */
		ret = -EIO;
	}

	return ret;
}