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
struct twl4030_usb {scalar_t__ usb_mode; scalar_t__ asleep; } ;

/* Variables and functions */
 scalar_t__ T2_USB_MODE_ULPI ; 
 int /*<<< orphan*/  twl4030_i2c_access (struct twl4030_usb*,int) ; 
 int /*<<< orphan*/  twl4030_phy_power (struct twl4030_usb*,int) ; 
 int /*<<< orphan*/  twl4030_usb_set_mode (struct twl4030_usb*,scalar_t__) ; 

__attribute__((used)) static void twl4030_phy_resume(struct twl4030_usb *twl)
{
	if (!twl->asleep)
		return;

	twl4030_phy_power(twl, 1);
	twl4030_i2c_access(twl, 1);
	twl4030_usb_set_mode(twl, twl->usb_mode);
	if (twl->usb_mode == T2_USB_MODE_ULPI)
		twl4030_i2c_access(twl, 0);
	twl->asleep = 0;
}