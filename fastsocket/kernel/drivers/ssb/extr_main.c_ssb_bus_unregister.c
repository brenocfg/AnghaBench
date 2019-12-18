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
struct ssb_bus {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_buses_lock () ; 
 int /*<<< orphan*/  ssb_buses_unlock () ; 
 int /*<<< orphan*/  ssb_devices_unregister (struct ssb_bus*) ; 
 int /*<<< orphan*/  ssb_iounmap (struct ssb_bus*) ; 
 int /*<<< orphan*/  ssb_pci_exit (struct ssb_bus*) ; 
 int /*<<< orphan*/  ssb_pcmcia_exit (struct ssb_bus*) ; 

void ssb_bus_unregister(struct ssb_bus *bus)
{
	ssb_buses_lock();
	ssb_devices_unregister(bus);
	list_del(&bus->list);
	ssb_buses_unlock();

	ssb_pcmcia_exit(bus);
	ssb_pci_exit(bus);
	ssb_iounmap(bus);
}