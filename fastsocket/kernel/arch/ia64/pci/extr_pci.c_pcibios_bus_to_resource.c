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
struct resource {int flags; scalar_t__ start; scalar_t__ end; } ;
struct TYPE_2__ {int flags; scalar_t__ start; scalar_t__ end; } ;
struct pci_window {unsigned long offset; TYPE_1__ resource; } ;
struct pci_dev {int dummy; } ;
struct pci_controller {int windows; struct pci_window* window; } ;
struct pci_bus_region {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 struct pci_controller* PCI_CONTROLLER (struct pci_dev*) ; 

void pcibios_bus_to_resource(struct pci_dev *dev,
		struct resource *res, struct pci_bus_region *region)
{
	struct pci_controller *controller = PCI_CONTROLLER(dev);
	unsigned long offset = 0;
	int i;

	for (i = 0; i < controller->windows; i++) {
		struct pci_window *window = &controller->window[i];
		if (!(window->resource.flags & res->flags))
			continue;
		if (window->resource.start - window->offset > region->start)
			continue;
		if (window->resource.end - window->offset < region->end)
			continue;
		offset = window->offset;
		break;
	}

	res->start = region->start + offset;
	res->end = region->end + offset;
}