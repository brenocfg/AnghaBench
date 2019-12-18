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
struct pci_dev {struct pci_bus* bus; } ;
struct pci_bus {struct pci_bus* parent; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static struct pci_bus *dca_pci_rc_from_dev(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct pci_bus *bus = pdev->bus;

	while (bus->parent)
		bus = bus->parent;

	return bus;
}