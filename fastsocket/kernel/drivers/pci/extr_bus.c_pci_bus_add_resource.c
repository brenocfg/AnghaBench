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
struct resource {int dummy; } ;
struct pci_bus_resource {unsigned int flags; int /*<<< orphan*/  list; struct resource* res; } ;
struct pci_bus {int /*<<< orphan*/  resources; int /*<<< orphan*/  dev; struct resource** resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PCI_BRIDGE_RESOURCE_NUM ; 
 int PCI_BUS_NUM_RESOURCES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,struct resource*) ; 
 struct pci_bus_resource* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void pci_bus_add_resource(struct pci_bus *bus, struct resource *res,
			  unsigned int flags)
{
	struct pci_bus_resource *bus_res;
	int i;

	for (i = PCI_BRIDGE_RESOURCE_NUM; i < PCI_BUS_NUM_RESOURCES; i++)
		if (bus->resource[i] == 0) {
			bus->resource[i] = res;
			return;
		}

	bus_res = kzalloc(sizeof(struct pci_bus_resource), GFP_KERNEL);
	if (!bus_res) {
		dev_err(&bus->dev, "can't add %pR resource\n", res);
		return;
	}

	bus_res->res = res;
	bus_res->flags = flags;
	list_add_tail(&bus_res->list, &bus->resources);
}