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
struct irq_desc {int status; int /*<<< orphan*/ * action; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int IRQ_DISABLED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int cached_irq_mask ; 
 int cached_master_mask ; 
 int cached_slave_mask ; 
 int /*<<< orphan*/  enable_8259A_irq (int) ; 
 int /*<<< orphan*/  handle_IRQ_event (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i8259A_lock ; 
 int inb (int) ; 
 struct irq_desc* irq_to_desc (int) ; 
 int /*<<< orphan*/  kstat_incr_irqs_this_cpu (int,struct irq_desc*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t piix4_master_intr(int irq, void *dev_id)
{
	int realirq;
	struct irq_desc *desc;
	unsigned long flags;

	spin_lock_irqsave(&i8259A_lock, flags);

	/* Find out what's interrupting in the PIIX4 master 8259 */
	outb(0x0c, 0x20);		/* OCW3 Poll command */
	realirq = inb(0x20);

	/*
	 * Bit 7 == 0 means invalid/spurious
	 */
	if (unlikely(!(realirq & 0x80)))
		goto out_unlock;

	realirq &= 7;

	if (unlikely(realirq == 2)) {
		outb(0x0c, 0xa0);
		realirq = inb(0xa0);

		if (unlikely(!(realirq & 0x80)))
			goto out_unlock;

		realirq = (realirq & 7) + 8;
	}

	/* mask and ack interrupt */
	cached_irq_mask |= 1 << realirq;
	if (unlikely(realirq > 7)) {
		inb(0xa1);
		outb(cached_slave_mask, 0xa1);
		outb(0x60 + (realirq & 7), 0xa0);
		outb(0x60 + 2, 0x20);
	} else {
		inb(0x21);
		outb(cached_master_mask, 0x21);
		outb(0x60 + realirq, 0x20);
	}

	spin_unlock_irqrestore(&i8259A_lock, flags);

	desc = irq_to_desc(realirq);

	/*
	 * handle this 'virtual interrupt' as a Cobalt one now.
	 */
	kstat_incr_irqs_this_cpu(realirq, desc);

	if (likely(desc->action != NULL))
		handle_IRQ_event(realirq, desc->action);

	if (!(desc->status & IRQ_DISABLED))
		enable_8259A_irq(realirq);

	return IRQ_HANDLED;

out_unlock:
	spin_unlock_irqrestore(&i8259A_lock, flags);
	return IRQ_NONE;
}