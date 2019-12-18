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
typedef  unsigned int u32 ;
struct bcma_drv_pci {TYPE_1__* host_controller; } ;
struct TYPE_2__ {unsigned int host_cfg_addr; } ;

/* Variables and functions */
 unsigned int BCMA_CORE_PCI_CFG_FUN_SHIFT ; 
 unsigned int BCMA_CORE_PCI_CFG_SLOT_SHIFT ; 
 int /*<<< orphan*/  BCMA_CORE_PCI_DLLP_LSREG ; 
 int BCMA_CORE_PCI_DLLP_LSREG_LINKUP ; 
 int /*<<< orphan*/  BCMA_CORE_PCI_SBTOPCI1 ; 
 int /*<<< orphan*/  BCMA_CORE_PCI_SBTOPCI_CFG0 ; 
 int bcma_pcie_read (struct bcma_drv_pci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcicore_write32 (struct bcma_drv_pci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 bcma_get_cfgspace_addr(struct bcma_drv_pci *pc, unsigned int dev,
			     unsigned int func, unsigned int off)
{
	u32 addr = 0;

	/* Issue config commands only when the data link is up (atleast
	 * one external pcie device is present).
	 */
	if (dev >= 2 || !(bcma_pcie_read(pc, BCMA_CORE_PCI_DLLP_LSREG)
			  & BCMA_CORE_PCI_DLLP_LSREG_LINKUP))
		goto out;

	/* Type 0 transaction */
	/* Slide the PCI window to the appropriate slot */
	pcicore_write32(pc, BCMA_CORE_PCI_SBTOPCI1, BCMA_CORE_PCI_SBTOPCI_CFG0);
	/* Calculate the address */
	addr = pc->host_controller->host_cfg_addr;
	addr |= (dev << BCMA_CORE_PCI_CFG_SLOT_SHIFT);
	addr |= (func << BCMA_CORE_PCI_CFG_FUN_SHIFT);
	addr |= (off & ~3);

out:
	return addr;
}