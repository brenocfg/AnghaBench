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
struct pci_dev {int /*<<< orphan*/  error_state; } ;
struct device_node {struct device_node* parent; } ;
struct TYPE_2__ {int eeh_mode; struct pci_dev* pcidev; } ;

/* Variables and functions */
 TYPE_1__* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  __eeh_mark_slot (struct device_node*,int) ; 
 struct device_node* find_device_pe (struct device_node*) ; 
 int /*<<< orphan*/  pci_channel_io_frozen ; 
 int /*<<< orphan*/  pcibios_find_pci_bus (struct device_node*) ; 

void eeh_mark_slot (struct device_node *dn, int mode_flag)
{
	struct pci_dev *dev;
	dn = find_device_pe (dn);

	/* Back up one, since config addrs might be shared */
	if (!pcibios_find_pci_bus(dn) && PCI_DN(dn->parent))
		dn = dn->parent;

	PCI_DN(dn)->eeh_mode |= mode_flag;

	/* Mark the pci device too */
	dev = PCI_DN(dn)->pcidev;
	if (dev)
		dev->error_state = pci_channel_io_frozen;

	__eeh_mark_slot(dn, mode_flag);
}