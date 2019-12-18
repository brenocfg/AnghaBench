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
typedef  int u16 ;
struct wm8350 {int dummy; } ;

/* Variables and functions */
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  WM8350_BATTERY_CHARGER_CONTROL_2 ; 
#define  WM8350_CHG_STS_FAST 130 
 int WM8350_CHG_STS_MASK ; 
#define  WM8350_CHG_STS_OFF 129 
#define  WM8350_CHG_STS_TRICKLE 128 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_batt_status(struct wm8350 *wm8350)
{
	u16 state;

	state = wm8350_reg_read(wm8350, WM8350_BATTERY_CHARGER_CONTROL_2);
	state &= WM8350_CHG_STS_MASK;

	switch (state) {
	case WM8350_CHG_STS_OFF:
		return POWER_SUPPLY_STATUS_DISCHARGING;

	case WM8350_CHG_STS_TRICKLE:
	case WM8350_CHG_STS_FAST:
		return POWER_SUPPLY_STATUS_CHARGING;

	default:
		return POWER_SUPPLY_STATUS_UNKNOWN;
	}
}