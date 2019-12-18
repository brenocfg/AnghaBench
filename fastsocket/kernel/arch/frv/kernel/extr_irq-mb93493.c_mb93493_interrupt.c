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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_BASE_MB93493 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  generic_handle_irq (scalar_t__) ; 
 int readl (void volatile*) ; 

__attribute__((used)) static irqreturn_t mb93493_interrupt(int irq, void *_piqsr)
{
	volatile void *piqsr = _piqsr;
	uint32_t iqsr;

	iqsr = readl(piqsr);
	iqsr = iqsr & (iqsr >> 16) & 0xffff;

	/* poll all the triggered IRQs */
	while (iqsr) {
		int irq;

		asm("scan %1,gr0,%0" : "=r"(irq) : "r"(iqsr));
		irq = 31 - irq;
		iqsr &= ~(1 << irq);

		generic_handle_irq(IRQ_BASE_MB93493 + irq);
	}

	return IRQ_HANDLED;
}