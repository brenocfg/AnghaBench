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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PCI_EXP_AER_FLAGS ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int /*<<< orphan*/  pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pcie_aer_get_firmware_first (struct pci_dev*) ; 
 int pcie_capability_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pci_enable_pcie_error_reporting(struct pci_dev *dev)
{
	if (pcie_aer_get_firmware_first(dev))
		return -EIO;

	if (!pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR))
		return -EIO;

	return pcie_capability_set_word(dev, PCI_EXP_DEVCTL, PCI_EXP_AER_FLAGS);
}