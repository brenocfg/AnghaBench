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
struct irqaction {int dummy; } ;
struct irq_desc {int status; int /*<<< orphan*/  lock; TYPE_1__* chip; struct irqaction* action; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* ack ) (unsigned int) ;int /*<<< orphan*/  (* mask ) (unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int IRQ_DISABLED ; 
 int IRQ_INPROGRESS ; 
 int IRQ_REPLAY ; 
 int IRQ_WAITING ; 
 int /*<<< orphan*/  handle_IRQ_event (unsigned int,struct irqaction*) ; 
 int /*<<< orphan*/  kstat_incr_irqs_this_cpu (unsigned int,struct irq_desc*) ; 
 int /*<<< orphan*/  note_interrupt (unsigned int,struct irq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void handle_prio_irq(unsigned int irq, struct irq_desc *desc)
{
	struct irqaction *action;
	irqreturn_t action_ret;

	spin_lock(&desc->lock);

	BUG_ON(desc->status & IRQ_INPROGRESS);

	desc->status &= ~(IRQ_REPLAY | IRQ_WAITING);
	kstat_incr_irqs_this_cpu(irq, desc);

	action = desc->action;
	if (unlikely(!action || (desc->status & IRQ_DISABLED)))
		goto out_mask;

	desc->status |= IRQ_INPROGRESS;
	spin_unlock(&desc->lock);

	action_ret = handle_IRQ_event(irq, action);

	/* XXX: There is no direct way to access noirqdebug, so check
	 * unconditionally for spurious irqs...
	 * Maybe this function should go to kernel/irq/chip.c? */
	note_interrupt(irq, desc, action_ret);

	spin_lock(&desc->lock);
	desc->status &= ~IRQ_INPROGRESS;

	if (desc->status & IRQ_DISABLED)
out_mask:
		desc->chip->mask(irq);

	/* ack unconditionally to unmask lower prio irqs */
	desc->chip->ack(irq);

	spin_unlock(&desc->lock);
}