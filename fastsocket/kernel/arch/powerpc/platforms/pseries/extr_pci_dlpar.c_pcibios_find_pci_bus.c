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
struct pci_dn {TYPE_1__* phb; } ;
struct pci_bus {int dummy; } ;
struct device_node {struct pci_dn* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 struct pci_bus* find_bus_among_children (int /*<<< orphan*/ ,struct device_node*) ; 

struct pci_bus *
pcibios_find_pci_bus(struct device_node *dn)
{
	struct pci_dn *pdn = dn->data;

	if (!pdn  || !pdn->phb || !pdn->phb->bus)
		return NULL;

	return find_bus_among_children(pdn->phb->bus, dn);
}