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
struct resource {unsigned long flags; scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  parent; } ;
struct pci_dev {int /*<<< orphan*/  dev; struct resource* resource; } ;
struct pci_bus {struct pci_dev* self; } ;

/* Variables and functions */
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_MEM ; 
 unsigned long IORESOURCE_PREFETCH ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int PCI_BRIDGE_RESOURCES ; 
 int PCI_NUM_RESOURCES ; 
 int /*<<< orphan*/  __pci_setup_bridge (struct pci_bus*,unsigned long) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,struct resource*) ; 
 int /*<<< orphan*/  release_child_resources (struct resource*) ; 
 int /*<<< orphan*/  release_resource (struct resource*) ; 

__attribute__((used)) static void pci_bridge_release_resources(struct pci_bus *bus,
					  unsigned long type)
{
	int idx;
	bool changed = false;
	struct pci_dev *dev;
	struct resource *r;
	unsigned long type_mask = IORESOURCE_IO | IORESOURCE_MEM |
				  IORESOURCE_PREFETCH;

	dev = bus->self;
	for (idx = PCI_BRIDGE_RESOURCES; idx < PCI_NUM_RESOURCES;
	     idx++) {
		r = &dev->resource[idx];
		if ((r->flags & type_mask) != type)
			continue;
		if (!r->parent)
			continue;
		/*
		 * if there are children under that, we should release them
		 *  all
		 */
		release_child_resources(r);
		if (!release_resource(r)) {
			dev_printk(KERN_DEBUG, &dev->dev,
				 "resource %d %pR released\n", idx, r);
			/* keep the old size */
			r->end = r->end - r->start;
			r->start = 0;
			r->flags = 0;
			changed = true;
		}
	}

	if (changed) {
		/* avoiding touch the one without PREF */
		if (type & IORESOURCE_PREFETCH)
			type = IORESOURCE_PREFETCH;
		__pci_setup_bridge(bus, type);
	}
}