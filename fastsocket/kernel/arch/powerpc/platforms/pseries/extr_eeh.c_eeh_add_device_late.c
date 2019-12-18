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
struct pci_dn {struct pci_dev* pcidev; } ;
struct pci_dev {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct pci_dn* PCI_DN (struct device_node*) ; 
 int /*<<< orphan*/  WARN_ON (struct pci_dev*) ; 
 int /*<<< orphan*/  eeh_subsystem_enabled ; 
 int /*<<< orphan*/  eeh_sysfs_add_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_addr_cache_insert_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 struct device_node* pci_device_to_OF_node (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void eeh_add_device_late(struct pci_dev *dev)
{
	struct device_node *dn;
	struct pci_dn *pdn;

	if (!dev || !eeh_subsystem_enabled)
		return;

	pr_debug("EEH: Adding device %s\n", pci_name(dev));

	dn = pci_device_to_OF_node(dev);
	pdn = PCI_DN(dn);
	if (pdn->pcidev == dev) {
		pr_debug("EEH: Already referenced !\n");
		return;
	}
	WARN_ON(pdn->pcidev);

	pci_dev_get (dev);
	pdn->pcidev = dev;

	pci_addr_cache_insert_device(dev);
	eeh_sysfs_add_device(dev);
}