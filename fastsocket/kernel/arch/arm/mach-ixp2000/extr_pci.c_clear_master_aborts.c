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

/* Variables and functions */
 int* IXP2000_PCI_CMDSTAT ; 
 int* IXP2000_PCI_CONTROL ; 
 int /*<<< orphan*/  ixp2000_reg_wrb (int*,int volatile) ; 
 int /*<<< orphan*/  ixp2000_reg_write (int*,int volatile) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

int
clear_master_aborts(void)
{
	volatile u32 temp;
	unsigned long flags;

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

	return 0;
}