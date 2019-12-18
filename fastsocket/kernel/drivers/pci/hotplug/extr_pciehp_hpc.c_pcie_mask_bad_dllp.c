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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct controller {TYPE_1__* pcie; } ;
struct TYPE_2__ {struct pci_dev* port; } ;

/* Variables and functions */
 int PCI_ERR_COR_BAD_DLLP ; 
 scalar_t__ PCI_ERR_COR_MASK ; 
 int /*<<< orphan*/  PCI_EXT_CAP_ID_ERR ; 
 int pci_find_ext_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 

__attribute__((used)) static inline int pcie_mask_bad_dllp(struct controller *ctrl)
{
	struct pci_dev *dev = ctrl->pcie->port;
	int pos;
	u32 reg;

	pos = pci_find_ext_capability(dev, PCI_EXT_CAP_ID_ERR);
	if (!pos)
		return 0;
	pci_read_config_dword(dev, pos + PCI_ERR_COR_MASK, &reg);
	if (reg & PCI_ERR_COR_BAD_DLLP)
		return 0;
	reg |= PCI_ERR_COR_BAD_DLLP;
	pci_write_config_dword(dev, pos + PCI_ERR_COR_MASK, reg);
	return 1;
}