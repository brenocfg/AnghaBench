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
typedef  scalar_t__ u32 ;
struct pci_dev {int state_saved; scalar_t__* saved_config_space; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/  pci_restore_ats_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_iov_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_msi_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_pcie_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_pcix_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,scalar_t__) ; 

int 
pci_restore_state(struct pci_dev *dev)
{
	int i;
	u32 val;

	if (!dev->state_saved)
		return 0;

	/* PCI Express register must be restored first */
	pci_restore_pcie_state(dev);
	pci_restore_ats_state(dev);

	/*
	 * The Base Address register should be programmed before the command
	 * register(s)
	 */
	for (i = 15; i >= 0; i--) {
		pci_read_config_dword(dev, i * 4, &val);
		if (val != dev->saved_config_space[i]) {
			dev_printk(KERN_DEBUG, &dev->dev, "restoring config "
				"space at offset %#x (was %#x, writing %#x)\n",
				i, val, (int)dev->saved_config_space[i]);
			pci_write_config_dword(dev,i * 4,
				dev->saved_config_space[i]);
		}
	}
	pci_restore_pcix_state(dev);
	pci_restore_msi_state(dev);
	pci_restore_iov_state(dev);

	dev->state_saved = false;

	return 0;
}