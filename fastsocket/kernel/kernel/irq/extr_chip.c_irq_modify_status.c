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
struct irq_desc {unsigned long status; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned long IRQF_MODIFY_MASK ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void irq_modify_status(unsigned int irq, unsigned long clr, unsigned long set)
{
	struct irq_desc *desc = irq_to_desc(irq);
	unsigned long flags;

	if (!desc)
		return;

	/* Sanitize flags */
	set &= IRQF_MODIFY_MASK;
	clr &= IRQF_MODIFY_MASK;

	spin_lock_irqsave(&desc->lock, flags);
	desc->status &= ~clr;
	desc->status |= set;
	spin_unlock_irqrestore(&desc->lock, flags);
}