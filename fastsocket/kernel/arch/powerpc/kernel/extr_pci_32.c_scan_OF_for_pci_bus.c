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
struct pci_controller {int /*<<< orphan*/  dn; } ;
struct pci_bus {TYPE_1__* self; struct pci_bus* parent; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 struct device_node* of_node_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 struct device_node* scan_OF_for_pci_dev (struct device_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct device_node *scan_OF_for_pci_bus(struct pci_bus *bus)
{
	struct device_node *parent, *np;

	/* Are we a root bus ? */
	if (bus->self == NULL || bus->parent == NULL) {
		struct pci_controller *hose = pci_bus_to_host(bus);
		if (hose == NULL)
			return NULL;
		return of_node_get(hose->dn);
	}

	/* not a root bus, we need to get our parent */
	parent = scan_OF_for_pci_bus(bus->parent);
	if (parent == NULL)
		return NULL;

	/* now iterate for children for a match */
	np = scan_OF_for_pci_dev(parent, bus->self->devfn);
	of_node_put(parent);

	return np;
}