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
struct pci_dev {struct pci_bus* subordinate; } ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_destroy_dev (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_remove_behind_bridge (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_remove_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_stop_bus_device (struct pci_dev*) ; 

void pci_remove_bus_device(struct pci_dev *dev)
{
	pci_stop_bus_device(dev);
	if (dev->subordinate) {
		struct pci_bus *b = dev->subordinate;

		pci_remove_behind_bridge(dev);
		pci_remove_bus(b);
		dev->subordinate = NULL;
	}

	pci_destroy_dev(dev);
}