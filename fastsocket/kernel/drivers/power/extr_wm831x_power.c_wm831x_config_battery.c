#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wm831x_pdata {struct wm831x_battery_pdata* battery; } ;
struct wm831x_battery_pdata {int /*<<< orphan*/  timeout; int /*<<< orphan*/  eoc_iterm; int /*<<< orphan*/  fast_ilim; int /*<<< orphan*/  vsel; int /*<<< orphan*/  trickle_ilim; scalar_t__ fast_enable; scalar_t__ off_mask; int /*<<< orphan*/  enable; } ;
struct wm831x {TYPE_1__* dev; } ;
struct TYPE_4__ {struct wm831x_pdata* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM831X_CHARGER_CONTROL_1 ; 
 int /*<<< orphan*/  WM831X_CHARGER_CONTROL_2 ; 
 int WM831X_CHG_ENA ; 
 int WM831X_CHG_ENA_MASK ; 
 int WM831X_CHG_FAST ; 
 int WM831X_CHG_FAST_ILIM_MASK ; 
 int WM831X_CHG_FAST_MASK ; 
 int WM831X_CHG_ITERM_MASK ; 
 int WM831X_CHG_OFF_MSK ; 
 int WM831X_CHG_TIME_MASK ; 
 int WM831X_CHG_TRKL_ILIM_MASK ; 
 int WM831X_CHG_VSEL_MASK ; 
 int /*<<< orphan*/  chg_times ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  eoc_iterms ; 
 int /*<<< orphan*/  fast_ilims ; 
 int /*<<< orphan*/  trickle_ilims ; 
 int /*<<< orphan*/  vsels ; 
 int /*<<< orphan*/  wm831x_battey_apply_config (struct wm831x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,char*,char*) ; 
 int /*<<< orphan*/  wm831x_reg_lock (struct wm831x*) ; 
 int wm831x_reg_unlock (struct wm831x*) ; 
 int wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void wm831x_config_battery(struct wm831x *wm831x)
{
	struct wm831x_pdata *wm831x_pdata = wm831x->dev->platform_data;
	struct wm831x_battery_pdata *pdata;
	int ret, reg1, reg2;

	if (!wm831x_pdata || !wm831x_pdata->battery) {
		dev_warn(wm831x->dev,
			 "No battery charger configuration\n");
		return;
	}

	pdata = wm831x_pdata->battery;

	reg1 = 0;
	reg2 = 0;

	if (!pdata->enable) {
		dev_info(wm831x->dev, "Battery charger disabled\n");
		return;
	}

	reg1 |= WM831X_CHG_ENA;
	if (pdata->off_mask)
		reg2 |= WM831X_CHG_OFF_MSK;
	if (pdata->fast_enable)
		reg1 |= WM831X_CHG_FAST;

	wm831x_battey_apply_config(wm831x, trickle_ilims,
				   ARRAY_SIZE(trickle_ilims),
				   pdata->trickle_ilim, &reg2,
				   "trickle charge current limit", "mA");

	wm831x_battey_apply_config(wm831x, vsels, ARRAY_SIZE(vsels),
				   pdata->vsel, &reg2,
				   "target voltage", "mV");

	wm831x_battey_apply_config(wm831x, fast_ilims, ARRAY_SIZE(fast_ilims),
				   pdata->fast_ilim, &reg2,
				   "fast charge current limit", "mA");

	wm831x_battey_apply_config(wm831x, eoc_iterms, ARRAY_SIZE(eoc_iterms),
				   pdata->eoc_iterm, &reg1,
				   "end of charge current threshold", "mA");

	wm831x_battey_apply_config(wm831x, chg_times, ARRAY_SIZE(chg_times),
				   pdata->timeout, &reg2,
				   "charger timeout", "min");

	ret = wm831x_reg_unlock(wm831x);
	if (ret != 0) {
		dev_err(wm831x->dev, "Failed to unlock registers: %d\n", ret);
		return;
	}

	ret = wm831x_set_bits(wm831x, WM831X_CHARGER_CONTROL_1,
			      WM831X_CHG_ENA_MASK |
			      WM831X_CHG_FAST_MASK |
			      WM831X_CHG_ITERM_MASK |
			      WM831X_CHG_ITERM_MASK,
			      reg1);
	if (ret != 0)
		dev_err(wm831x->dev, "Failed to set charger control 1: %d\n",
			ret);

	ret = wm831x_set_bits(wm831x, WM831X_CHARGER_CONTROL_2,
			      WM831X_CHG_OFF_MSK |
			      WM831X_CHG_TIME_MASK |
			      WM831X_CHG_FAST_ILIM_MASK |
			      WM831X_CHG_TRKL_ILIM_MASK |
			      WM831X_CHG_VSEL_MASK,
			      reg2);
	if (ret != 0)
		dev_err(wm831x->dev, "Failed to set charger control 2: %d\n",
			ret);

	wm831x_reg_lock(wm831x);
}