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
 int IRQ_IXP23XX_INTA ; 
 int* IXP23XX_PCI_XSCALE_INT_ENABLE ; 

__attribute__((used)) static void ixp23xx_pci_irq_mask(unsigned int irq)
{
	*IXP23XX_PCI_XSCALE_INT_ENABLE &= ~(1 << (IRQ_IXP23XX_INTA + 27 - irq));
}