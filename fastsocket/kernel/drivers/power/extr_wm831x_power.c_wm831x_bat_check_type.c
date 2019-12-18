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
struct wm831x {int dummy; } ;

/* Variables and functions */
 int POWER_SUPPLY_CHARGE_TYPE_FAST ; 
 int POWER_SUPPLY_CHARGE_TYPE_NONE ; 
 int POWER_SUPPLY_CHARGE_TYPE_TRICKLE ; 
 int /*<<< orphan*/  WM831X_CHARGER_STATUS ; 
#define  WM831X_CHG_STATE_FAST 131 
#define  WM831X_CHG_STATE_FAST_OT 130 
 int WM831X_CHG_STATE_MASK ; 
#define  WM831X_CHG_STATE_TRICKLE 129 
#define  WM831X_CHG_STATE_TRICKLE_OT 128 
 int wm831x_reg_read (struct wm831x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_bat_check_type(struct wm831x *wm831x, int *type)
{
	int ret;

	ret = wm831x_reg_read(wm831x, WM831X_CHARGER_STATUS);
	if (ret < 0)
		return ret;

	switch (ret & WM831X_CHG_STATE_MASK) {
	case WM831X_CHG_STATE_TRICKLE:
	case WM831X_CHG_STATE_TRICKLE_OT:
		*type = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
		break;
	case WM831X_CHG_STATE_FAST:
	case WM831X_CHG_STATE_FAST_OT:
		*type = POWER_SUPPLY_CHARGE_TYPE_FAST;
		break;
	default:
		*type = POWER_SUPPLY_CHARGE_TYPE_NONE;
		break;
	}

	return 0;
}