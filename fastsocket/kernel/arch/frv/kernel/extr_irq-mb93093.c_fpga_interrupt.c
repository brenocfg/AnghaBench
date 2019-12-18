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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_BASE_FPGA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int __get_IFR () ; 
 int __get_IMR () ; 
 int /*<<< orphan*/  generic_irq_handle (scalar_t__) ; 

__attribute__((used)) static irqreturn_t fpga_interrupt(int irq, void *_mask)
{
	uint16_t imr, mask = (unsigned long) _mask;

	imr = __get_IMR();
	mask = mask & ~imr & __get_IFR();

	/* poll all the triggered IRQs */
	while (mask) {
		int irq;

		asm("scan %1,gr0,%0" : "=r"(irq) : "r"(mask));
		irq = 31 - irq;
		mask &= ~(1 << irq);

		generic_irq_handle(IRQ_BASE_FPGA + irq);
	}

	return IRQ_HANDLED;
}