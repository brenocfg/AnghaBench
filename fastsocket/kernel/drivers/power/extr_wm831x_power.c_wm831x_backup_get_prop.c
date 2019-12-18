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
struct wm831x_power {struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct power_supply {TYPE_1__* dev; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_PRESENT 130 
#define  POWER_SUPPLY_PROP_STATUS 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int /*<<< orphan*/  WM831X_AUX_BKUP_BATT ; 
 int /*<<< orphan*/  WM831X_BACKUP_CHARGER_CONTROL ; 
 int WM831X_BKUP_CHG_STS ; 
 struct wm831x_power* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int wm831x_power_read_voltage (struct wm831x*,int /*<<< orphan*/ ,union power_supply_propval*) ; 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_backup_get_prop(struct power_supply *psy,
				  enum power_supply_property psp,
				  union power_supply_propval *val)
{
	struct wm831x_power *wm831x_power = dev_get_drvdata(psy->dev->parent);
	struct wm831x *wm831x = wm831x_power->wm831x;
	int ret = 0;

	ret = wm831x_reg_read(wm831x, WM831X_BACKUP_CHARGER_CONTROL);
	if (ret < 0)
		return ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		if (ret & WM831X_BKUP_CHG_STS)
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		break;

	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = wm831x_power_read_voltage(wm831x, WM831X_AUX_BKUP_BATT,
						val);
		break;

	case POWER_SUPPLY_PROP_PRESENT:
		if (ret & WM831X_BKUP_CHG_STS)
			val->intval = 1;
		else
			val->intval = 0;
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}