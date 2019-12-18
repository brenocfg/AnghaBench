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
struct pxa25x_udc {scalar_t__ ep0state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DBG_VERBOSE ; 
 scalar_t__ EP0_STALL ; 
 int UDCCS0 ; 
 int UDCCS0_FST ; 
 int UDCCS0_FTF ; 
 int UDCCS0_SST ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  start_watchdog (struct pxa25x_udc*) ; 

__attribute__((used)) static void udc_watchdog(unsigned long _dev)
{
	struct pxa25x_udc	*dev = (void *)_dev;

	local_irq_disable();
	if (dev->ep0state == EP0_STALL
			&& (UDCCS0 & UDCCS0_FST) == 0
			&& (UDCCS0 & UDCCS0_SST) == 0) {
		UDCCS0 = UDCCS0_FST|UDCCS0_FTF;
		DBG(DBG_VERBOSE, "ep0 re-stall\n");
		start_watchdog(dev);
	}
	local_irq_enable();
}