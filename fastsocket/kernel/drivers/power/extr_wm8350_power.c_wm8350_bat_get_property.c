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
union power_supply_propval {int intval; } ;
struct wm8350 {int dummy; } ;
struct power_supply {TYPE_1__* dev; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 132 
#define  POWER_SUPPLY_PROP_HEALTH 131 
#define  POWER_SUPPLY_PROP_ONLINE 130 
#define  POWER_SUPPLY_PROP_STATUS 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int WM8350_BATT_SUPPLY ; 
 struct wm8350* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int wm8350_bat_check_health (struct wm8350*) ; 
 int wm8350_bat_get_charge_type (struct wm8350*) ; 
 int wm8350_batt_status (struct wm8350*) ; 
 int wm8350_get_supplies (struct wm8350*) ; 
 int wm8350_read_battery_uvolts (struct wm8350*) ; 

__attribute__((used)) static int wm8350_bat_get_property(struct power_supply *psy,
				   enum power_supply_property psp,
				   union power_supply_propval *val)
{
	struct wm8350 *wm8350 = dev_get_drvdata(psy->dev->parent);
	int ret = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = wm8350_batt_status(wm8350);
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = !!(wm8350_get_supplies(wm8350) &
				 WM8350_BATT_SUPPLY);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = wm8350_read_battery_uvolts(wm8350);
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		val->intval = wm8350_bat_check_health(wm8350);
		break;
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		val->intval = wm8350_bat_get_charge_type(wm8350);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}