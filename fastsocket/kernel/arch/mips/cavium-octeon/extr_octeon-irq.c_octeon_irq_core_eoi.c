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
struct irq_desc {int status; } ;

/* Variables and functions */
 int IRQ_DISABLED ; 
 unsigned int OCTEON_IRQ_SW0 ; 
 struct irq_desc* irq_desc ; 
 int /*<<< orphan*/  set_c0_status (int) ; 

__attribute__((used)) static void octeon_irq_core_eoi(unsigned int irq)
{
	struct irq_desc *desc = irq_desc + irq;
	unsigned int bit = irq - OCTEON_IRQ_SW0;
	/*
	 * If an IRQ is being processed while we are disabling it the
	 * handler will attempt to unmask the interrupt after it has
	 * been disabled.
	 */
	if (desc->status & IRQ_DISABLED)
		return;

	/* There is a race here.  We should fix it.  */

	/*
	 * We don't need to disable IRQs to make these atomic since
	 * they are already disabled earlier in the low level
	 * interrupt code.
	 */
	set_c0_status(0x100 << bit);
}