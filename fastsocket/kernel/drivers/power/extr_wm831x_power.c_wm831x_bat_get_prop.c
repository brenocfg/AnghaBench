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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct wm831x_power {struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
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
 int /*<<< orphan*/  WM831X_AUX_BATT ; 
 int /*<<< orphan*/  WM831X_PWR_SRC_BATT ; 
 struct wm831x_power* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int wm831x_bat_check_health (struct wm831x*,int /*<<< orphan*/ *) ; 
 int wm831x_bat_check_status (struct wm831x*,int /*<<< orphan*/ *) ; 
 int wm831x_bat_check_type (struct wm831x*,int /*<<< orphan*/ *) ; 
 int wm831x_power_check_online (struct wm831x*,int /*<<< orphan*/ ,union power_supply_propval*) ; 
 int wm831x_power_read_voltage (struct wm831x*,int /*<<< orphan*/ ,union power_supply_propval*) ; 

__attribute__((used)) static int wm831x_bat_get_prop(struct power_supply *psy,
			       enum power_supply_property psp,
			       union power_supply_propval *val)
{
	struct wm831x_power *wm831x_power = dev_get_drvdata(psy->dev->parent);
	struct wm831x *wm831x = wm831x_power->wm831x;
	int ret = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		ret = wm831x_bat_check_status(wm831x, &val->intval);
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		ret = wm831x_power_check_online(wm831x, WM831X_PWR_SRC_BATT,
						val);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = wm831x_power_read_voltage(wm831x, WM831X_AUX_BATT, val);
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		ret = wm831x_bat_check_health(wm831x, &val->intval);
		break;
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = wm831x_bat_check_type(wm831x, &val->intval);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}