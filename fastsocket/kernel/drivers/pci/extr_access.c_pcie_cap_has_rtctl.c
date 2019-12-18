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
 int PCI_EXP_TYPE_RC_EC ; 
 int PCI_EXP_TYPE_ROOT_PORT ; 
 int pci_pcie_type (struct pci_dev const*) ; 
 int pcie_cap_version (struct pci_dev const*) ; 

__attribute__((used)) static inline bool pcie_cap_has_rtctl(const struct pci_dev *dev)
{
	int type = pci_pcie_type(dev);

	return pcie_cap_version(dev) > 1 ||
	       type == PCI_EXP_TYPE_ROOT_PORT ||
	       type == PCI_EXP_TYPE_RC_EC;
}