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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct pci_bus {int number; int subordinate; int /*<<< orphan*/  bridge; TYPE_1__ dev; } ;

/* Variables and functions */
 struct pci_bus* pci_add_new_bus (struct pci_bus*,int /*<<< orphan*/ *,int) ; 
 int pci_bus_add_child (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 struct pci_bus* pci_find_bus (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_remove_bus (struct pci_bus*) ; 

__attribute__((used)) static struct pci_bus *virtfn_add_bus(struct pci_bus *bus, int busnr)
{
	int rc;
	struct pci_bus *child;

	if (bus->number == busnr)
		return bus;

	child = pci_find_bus(pci_domain_nr(bus), busnr);
	if (child)
		return child;

	child = pci_add_new_bus(bus, NULL, busnr);
	if (!child)
		return NULL;

	child->subordinate = busnr;
	child->dev.parent = bus->bridge;
	rc = pci_bus_add_child(child);
	if (rc) {
		pci_remove_bus(child);
		return NULL;
	}

	return child;
}