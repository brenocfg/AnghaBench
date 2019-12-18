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
struct pt_regs {int ARM_pc; } ;

/* Variables and functions */
 int* IXP2000_PCI_CMDSTAT ; 
 int* IXP2000_PCI_CONTROL ; 
 int /*<<< orphan*/  ixp2000_reg_wrb (int*,int volatile) ; 
 int /*<<< orphan*/  ixp2000_reg_write (int*,int volatile) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int pci_master_aborts ; 

int ixp2000_pci_abort_handler(unsigned long addr, unsigned int fsr, struct pt_regs *regs)
{

	volatile u32 temp;
	unsigned long flags;

	pci_master_aborts = 1;

	local_irq_save(flags);
	temp = *(IXP2000_PCI_CONTROL);
	if (temp & ((1 << 8) | (1 << 5))) {
		ixp2000_reg_wrb(IXP2000_PCI_CONTROL, temp);
	}

	temp = *(IXP2000_PCI_CMDSTAT);
	if (temp & (1 << 29)) {
		while (temp & (1 << 29)) {	
			ixp2000_reg_write(IXP2000_PCI_CMDSTAT, temp);
			temp = *(IXP2000_PCI_CMDSTAT);
		}
	}
	local_irq_restore(flags);

	/*
	 * If it was an imprecise abort, then we need to correct the
	 * return address to be _after_ the instruction.
	 */
	if (fsr & (1 << 10))
		regs->ARM_pc += 4;

	return 0;
}