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
 int /*<<< orphan*/  WM8350_BATTERY_CHARGER_CONTROL_2 ; 
 int WM8350_BATT_SUPPLY ; 
 int WM8350_CHG_ISEL_MASK ; 
 int /*<<< orphan*/  WM8350_COMPARATOR_OVERRIDES ; 
 int WM8350_LINE_SUPPLY ; 
 int /*<<< orphan*/  WM8350_MISC_OVERRIDES ; 
 int /*<<< orphan*/  WM8350_STATE_MACHINE_STATUS ; 
 int WM8350_USB_LIMIT_OVRDE ; 
 int WM8350_USB_SM_100_SLV ; 
 int WM8350_USB_SM_500_SLV ; 
 int WM8350_USB_SM_MASK ; 
 int WM8350_USB_SM_SHIFT ; 
 int WM8350_USB_SM_STDBY_SLV ; 
 int WM8350_USB_SUPPLY ; 
 int WM8350_WALL_FB_OVRDE ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_get_supplies(struct wm8350 *wm8350)
{
	u16 sm, ov, co, chrg;
	int supplies = 0;

	sm = wm8350_reg_read(wm8350, WM8350_STATE_MACHINE_STATUS);
	ov = wm8350_reg_read(wm8350, WM8350_MISC_OVERRIDES);
	co = wm8350_reg_read(wm8350, WM8350_COMPARATOR_OVERRIDES);
	chrg = wm8350_reg_read(wm8350, WM8350_BATTERY_CHARGER_CONTROL_2);

	/* USB_SM */
	sm = (sm & WM8350_USB_SM_MASK) >> WM8350_USB_SM_SHIFT;

	/* CHG_ISEL */
	chrg &= WM8350_CHG_ISEL_MASK;

	/* If the USB state machine is active then we're using that with or
	 * without battery, otherwise check for wall supply */
	if (((sm == WM8350_USB_SM_100_SLV) ||
	     (sm == WM8350_USB_SM_500_SLV) ||
	     (sm == WM8350_USB_SM_STDBY_SLV))
	    && !(ov & WM8350_USB_LIMIT_OVRDE))
		supplies = WM8350_USB_SUPPLY;
	else if (((sm == WM8350_USB_SM_100_SLV) ||
		  (sm == WM8350_USB_SM_500_SLV) ||
		  (sm == WM8350_USB_SM_STDBY_SLV))
		 && (ov & WM8350_USB_LIMIT_OVRDE) && (chrg == 0))
		supplies = WM8350_USB_SUPPLY | WM8350_BATT_SUPPLY;
	else if (co & WM8350_WALL_FB_OVRDE)
		supplies = WM8350_LINE_SUPPLY;
	else
		supplies = WM8350_BATT_SUPPLY;

	return supplies;
}