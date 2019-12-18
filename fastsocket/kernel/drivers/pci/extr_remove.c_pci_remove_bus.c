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
struct pci_bus {int /*<<< orphan*/  dev; int /*<<< orphan*/  is_added; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int /*<<< orphan*/  pci_proc_detach_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_remove_legacy_files (struct pci_bus*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void pci_remove_bus(struct pci_bus *pci_bus)
{
	pci_proc_detach_bus(pci_bus);

	down_write(&pci_bus_sem);
	list_del(&pci_bus->node);
	up_write(&pci_bus_sem);
	if (!pci_bus->is_added)
		return;

	pci_remove_legacy_files(pci_bus);
	device_unregister(&pci_bus->dev);
}