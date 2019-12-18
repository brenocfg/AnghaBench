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
struct TYPE_2__ {int iTCO_version; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  smi_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCO1_STS ; 
 int /*<<< orphan*/  TCO_RLD ; 
 int /*<<< orphan*/  heartbeat ; 
 int /*<<< orphan*/  iTCO_vendor_pre_keepalive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ iTCO_wdt_private ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iTCO_wdt_keepalive(void)
{
	spin_lock(&iTCO_wdt_private.io_lock);

	iTCO_vendor_pre_keepalive(iTCO_wdt_private.smi_res, heartbeat);

	/* Reload the timer by writing to the TCO Timer Counter register */
	if (iTCO_wdt_private.iTCO_version == 2)
		outw(0x01, TCO_RLD);
	else if (iTCO_wdt_private.iTCO_version == 1) {
		/* Reset the timeout status bit so that the timer
		 * needs to count down twice again before rebooting */
		outw(0x0008, TCO1_STS);	/* write 1 to clear bit */

		outb(0x01, TCO_RLD);
	}

	spin_unlock(&iTCO_wdt_private.io_lock);
	return 0;
}