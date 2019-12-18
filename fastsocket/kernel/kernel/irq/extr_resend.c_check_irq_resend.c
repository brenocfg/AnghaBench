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
struct irq_desc {unsigned int status; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* retrigger ) (unsigned int) ;int /*<<< orphan*/  (* enable ) (unsigned int) ;} ;

/* Variables and functions */
 unsigned int IRQ_LEVEL ; 
 unsigned int IRQ_PENDING ; 
 unsigned int IRQ_REPLAY ; 
 int /*<<< orphan*/  irqs_resend ; 
 int /*<<< orphan*/  resend_tasklet ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void check_irq_resend(struct irq_desc *desc, unsigned int irq)
{
	unsigned int status = desc->status;

	/*
	 * Make sure the interrupt is enabled, before resending it:
	 */
	desc->chip->enable(irq);

	/*
	 * We do not resend level type interrupts. Level type
	 * interrupts are resent by hardware when they are still
	 * active.
	 */
	if ((status & (IRQ_LEVEL | IRQ_PENDING | IRQ_REPLAY)) == IRQ_PENDING) {
		desc->status = (status & ~IRQ_PENDING) | IRQ_REPLAY;

		if (!desc->chip->retrigger || !desc->chip->retrigger(irq)) {
#ifdef CONFIG_HARDIRQS_SW_RESEND
			/* Set it pending and activate the softirq: */
			set_bit(irq, irqs_resend);
			tasklet_schedule(&resend_tasklet);
#endif
		}
	}
}