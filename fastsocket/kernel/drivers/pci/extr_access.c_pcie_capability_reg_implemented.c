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
#define  PCI_EXP_DEVCAP 145 
#define  PCI_EXP_DEVCAP2 144 
#define  PCI_EXP_DEVCTL 143 
#define  PCI_EXP_DEVCTL2 142 
#define  PCI_EXP_DEVSTA 141 
#define  PCI_EXP_FLAGS 140 
#define  PCI_EXP_LNKCAP 139 
#define  PCI_EXP_LNKCAP2 138 
#define  PCI_EXP_LNKCTL 137 
#define  PCI_EXP_LNKCTL2 136 
#define  PCI_EXP_LNKSTA 135 
#define  PCI_EXP_LNKSTA2 134 
#define  PCI_EXP_RTCAP 133 
#define  PCI_EXP_RTCTL 132 
#define  PCI_EXP_RTSTA 131 
#define  PCI_EXP_SLTCAP 130 
#define  PCI_EXP_SLTCTL 129 
#define  PCI_EXP_SLTSTA 128 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int pcie_cap_has_devctl (struct pci_dev*) ; 
 int pcie_cap_has_lnkctl (struct pci_dev*) ; 
 int pcie_cap_has_rtctl (struct pci_dev*) ; 
 int pcie_cap_has_sltctl (struct pci_dev*) ; 
 int pcie_cap_version (struct pci_dev*) ; 

__attribute__((used)) static bool pcie_capability_reg_implemented(struct pci_dev *dev, int pos)
{
	if (!pci_is_pcie(dev))
		return false;

	switch (pos) {
	case PCI_EXP_FLAGS:
		return true;
	case PCI_EXP_DEVCAP:
	case PCI_EXP_DEVCTL:
	case PCI_EXP_DEVSTA:
		return pcie_cap_has_devctl(dev);
	case PCI_EXP_LNKCAP:
	case PCI_EXP_LNKCTL:
	case PCI_EXP_LNKSTA:
		return pcie_cap_has_lnkctl(dev);
	case PCI_EXP_SLTCAP:
	case PCI_EXP_SLTCTL:
	case PCI_EXP_SLTSTA:
		return pcie_cap_has_sltctl(dev);
	case PCI_EXP_RTCTL:
	case PCI_EXP_RTCAP:
	case PCI_EXP_RTSTA:
		return pcie_cap_has_rtctl(dev);
	case PCI_EXP_DEVCAP2:
	case PCI_EXP_DEVCTL2:
	case PCI_EXP_LNKCAP2:
	case PCI_EXP_LNKCTL2:
	case PCI_EXP_LNKSTA2:
		return pcie_cap_version(dev) > 1;
	default:
		return false;
	}
}