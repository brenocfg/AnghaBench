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
struct irq_desc {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmask ) (unsigned int) ;int /*<<< orphan*/  (* ack ) (unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned int IRQ_IXP23XX_INTA ; 
 unsigned int IRQ_IXP23XX_INTB ; 
 int* IXP23XX_PCI_XSCALE_INT_STATUS ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 

__attribute__((used)) static void pci_handler(unsigned int irq, struct irq_desc *desc)
{
	u32 pci_interrupt;
	unsigned int irqno;

	pci_interrupt = *IXP23XX_PCI_XSCALE_INT_STATUS;

	desc->chip->ack(irq);

	/* See which PCI_INTA, or PCI_INTB interrupted */
	if (pci_interrupt & (1 << 26)) {
		irqno = IRQ_IXP23XX_INTB;
	} else if (pci_interrupt & (1 << 27)) {
		irqno = IRQ_IXP23XX_INTA;
	} else {
		BUG();
	}

	generic_handle_irq(irqno);

	desc->chip->unmask(irq);
}