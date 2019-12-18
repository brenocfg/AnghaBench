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
struct twl4030_usb {int dummy; } ;
struct otg_transceiver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  twl4030_phy_resume (struct twl4030_usb*) ; 
 int /*<<< orphan*/  twl4030_phy_suspend (struct twl4030_usb*,int) ; 
 struct twl4030_usb* xceiv_to_twl (struct otg_transceiver*) ; 

__attribute__((used)) static int twl4030_set_suspend(struct otg_transceiver *x, int suspend)
{
	struct twl4030_usb *twl = xceiv_to_twl(x);

	if (suspend)
		twl4030_phy_suspend(twl, 1);
	else
		twl4030_phy_resume(twl);

	return 0;
}