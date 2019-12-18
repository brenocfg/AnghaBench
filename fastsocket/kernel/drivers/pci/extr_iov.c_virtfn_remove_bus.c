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
struct pci_bus {int number; int /*<<< orphan*/  devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 
 struct pci_bus* pci_find_bus (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_remove_bus (struct pci_bus*) ; 

__attribute__((used)) static void virtfn_remove_bus(struct pci_bus *bus, int busnr)
{
	struct pci_bus *child;

	if (bus->number == busnr)
		return;

	child = pci_find_bus(pci_domain_nr(bus), busnr);
	BUG_ON(!child);

	if (list_empty(&child->devices))
		pci_remove_bus(child);
}