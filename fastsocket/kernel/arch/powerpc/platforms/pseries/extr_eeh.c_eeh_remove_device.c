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
struct pci_dev {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pcidev; } ;

/* Variables and functions */
 TYPE_1__* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  eeh_subsystem_enabled ; 
 int /*<<< orphan*/  eeh_sysfs_remove_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_addr_cache_remove_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void eeh_remove_device(struct pci_dev *dev)
{
	struct device_node *dn;
	if (!dev || !eeh_subsystem_enabled)
		return;

	/* Unregister the device with the EEH/PCI address search system */
	pr_debug("EEH: Removing device %s\n", pci_name(dev));

	dn = pci_device_to_OF_node(dev);
	if (PCI_DN(dn)->pcidev == NULL) {
		pr_debug("EEH: Not referenced !\n");
		return;
	}
	PCI_DN(dn)->pcidev = NULL;
	pci_dev_put (dev);

	pci_addr_cache_remove_device(dev);
	eeh_sysfs_remove_device(dev);
}