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
struct twl4030_usb {int asleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  twl4030_phy_power (struct twl4030_usb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl4030_phy_suspend(struct twl4030_usb *twl, int controller_off)
{
	if (twl->asleep)
		return;

	twl4030_phy_power(twl, 0);
	twl->asleep = 1;
}