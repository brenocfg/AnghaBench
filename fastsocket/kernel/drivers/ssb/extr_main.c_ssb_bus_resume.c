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
struct TYPE_2__ {scalar_t__ setup_done; } ;
struct ssb_bus {int /*<<< orphan*/  chipco; TYPE_1__ pcicore; int /*<<< orphan*/ * mapped_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ssb_bus_may_powerdown (struct ssb_bus*) ; 
 int ssb_bus_powerup (struct ssb_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_chipco_resume (int /*<<< orphan*/ *) ; 
 int ssb_pcmcia_hardware_setup (struct ssb_bus*) ; 

int ssb_bus_resume(struct ssb_bus *bus)
{
	int err;

	/* Reset HW state information in memory, so that HW is
	 * completely reinitialized. */
	bus->mapped_device = NULL;
#ifdef CONFIG_SSB_DRIVER_PCICORE
	bus->pcicore.setup_done = 0;
#endif

	err = ssb_bus_powerup(bus, 0);
	if (err)
		return err;
	err = ssb_pcmcia_hardware_setup(bus);
	if (err) {
		ssb_bus_may_powerdown(bus);
		return err;
	}
	ssb_chipco_resume(&bus->chipco);
	ssb_bus_may_powerdown(bus);

	return 0;
}