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
typedef  int u32 ;
struct pci_dev {scalar_t__ subordinate; int /*<<< orphan*/  dev; } ;
struct hpp_type2 {int revision; int unc_err_mask_and; int unc_err_mask_or; int unc_err_sever_and; int unc_err_sever_or; int cor_err_mask_and; int cor_err_mask_or; int adv_err_cap_and; int adv_err_cap_or; int /*<<< orphan*/  pci_exp_lnkctl_or; int /*<<< orphan*/  pci_exp_lnkctl_and; int /*<<< orphan*/  pci_exp_devctl_or; int /*<<< orphan*/  pci_exp_devctl_and; } ;

/* Variables and functions */
 scalar_t__ PCI_ERR_CAP ; 
 scalar_t__ PCI_ERR_COR_MASK ; 
 scalar_t__ PCI_ERR_UNCOR_MASK ; 
 scalar_t__ PCI_ERR_UNCOR_SEVER ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  pcie_capability_clear_and_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void program_hpp_type2(struct pci_dev *dev, struct hpp_type2 *hpp)
{
	int pos;
	u32 reg32;

	if (!hpp)
		return;

	if (hpp->revision > 1) {
		dev_warn(&dev->dev, "PCIe settings rev %d not supported\n",
			 hpp->revision);
		return;
	}

	/* Initialize Device Control Register */
	pcie_capability_clear_and_set_word(dev, PCI_EXP_DEVCTL,
			~hpp->pci_exp_devctl_and, hpp->pci_exp_devctl_or);

	/* Initialize Link Control Register */
	if (dev->subordinate)
		pcie_capability_clear_and_set_word(dev, PCI_EXP_LNKCTL,
			~hpp->pci_exp_lnkctl_and, hpp->pci_exp_lnkctl_or);

	/* Find Advanced Error Reporting Enhanced Capability */
	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR);
	if (!pos)
		return;

	/* Initialize Uncorrectable Error Mask Register */
	pci_read_config_dword(dev, pos + PCI_ERR_UNCOR_MASK, &reg32);
	reg32 = (reg32 & hpp->unc_err_mask_and) | hpp->unc_err_mask_or;
	pci_write_config_dword(dev, pos + PCI_ERR_UNCOR_MASK, reg32);

	/* Initialize Uncorrectable Error Severity Register */
	pci_read_config_dword(dev, pos + PCI_ERR_UNCOR_SEVER, &reg32);
	reg32 = (reg32 & hpp->unc_err_sever_and) | hpp->unc_err_sever_or;
	pci_write_config_dword(dev, pos + PCI_ERR_UNCOR_SEVER, reg32);

	/* Initialize Correctable Error Mask Register */
	pci_read_config_dword(dev, pos + PCI_ERR_COR_MASK, &reg32);
	reg32 = (reg32 & hpp->cor_err_mask_and) | hpp->cor_err_mask_or;
	pci_write_config_dword(dev, pos + PCI_ERR_COR_MASK, reg32);

	/* Initialize Advanced Error Capabilities and Control Register */
	pci_read_config_dword(dev, pos + PCI_ERR_CAP, &reg32);
	reg32 = (reg32 & hpp->adv_err_cap_and) | hpp->adv_err_cap_or;
	pci_write_config_dword(dev, pos + PCI_ERR_CAP, reg32);

	/*
	 * FIXME: The following two registers are not supported yet.
	 *
	 *   o Secondary Uncorrectable Error Severity Register
	 *   o Secondary Uncorrectable Error Mask Register
	 */
}