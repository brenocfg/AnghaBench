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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct aspm_register_info {int support; int latency_encoding_l0s; int latency_encoding_l1; int enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_LNKCAP ; 
 int PCI_EXP_LNKCAP_ASPMS ; 
 int PCI_EXP_LNKCAP_L0SEL ; 
 int PCI_EXP_LNKCAP_L1EL ; 
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int PCI_EXP_LNKCTL_ASPMC ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void pcie_get_aspm_reg(struct pci_dev *pdev,
			      struct aspm_register_info *info)
{
	u16 reg16;
	u32 reg32;

	pcie_capability_read_dword(pdev, PCI_EXP_LNKCAP, &reg32);
	info->support = (reg32 & PCI_EXP_LNKCAP_ASPMS) >> 10;
	info->latency_encoding_l0s = (reg32 & PCI_EXP_LNKCAP_L0SEL) >> 12;
	info->latency_encoding_l1  = (reg32 & PCI_EXP_LNKCAP_L1EL) >> 15;
	pcie_capability_read_word(pdev, PCI_EXP_LNKCTL, &reg16);
	info->enabled = reg16 & PCI_EXP_LNKCTL_ASPMC;
}