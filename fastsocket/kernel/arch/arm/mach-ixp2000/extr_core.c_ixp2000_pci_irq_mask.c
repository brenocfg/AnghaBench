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

/* Variables and functions */
 unsigned int IRQ_IXP2000_PCIA ; 
 unsigned int IRQ_IXP2000_PCIB ; 
 unsigned long* IXP2000_PCI_XSCALE_INT_ENABLE ; 
 int /*<<< orphan*/  ixp2000_reg_wrb (unsigned long*,unsigned long) ; 

__attribute__((used)) static void ixp2000_pci_irq_mask(unsigned int irq)
{
	unsigned long temp = *IXP2000_PCI_XSCALE_INT_ENABLE;
	if (irq == IRQ_IXP2000_PCIA)
		ixp2000_reg_wrb(IXP2000_PCI_XSCALE_INT_ENABLE, (temp & ~(1 << 26)));
	else if (irq == IRQ_IXP2000_PCIB)
		ixp2000_reg_wrb(IXP2000_PCI_XSCALE_INT_ENABLE, (temp & ~(1 << 27)));
}