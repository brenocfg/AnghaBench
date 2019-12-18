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
 int IRQ_INPROGRESS ; 
 int IRQ_WAITING ; 
 int /*<<< orphan*/  cobalt_lock ; 
 int /*<<< orphan*/  enable_cobalt_irq (unsigned int) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int startup_cobalt_irq(unsigned int irq)
{
	unsigned long flags;
	struct irq_desc *desc = irq_to_desc(irq);

	spin_lock_irqsave(&cobalt_lock, flags);
	if ((desc->status & (IRQ_DISABLED | IRQ_INPROGRESS | IRQ_WAITING)))
		desc->status &= ~(IRQ_DISABLED | IRQ_INPROGRESS | IRQ_WAITING);
	enable_cobalt_irq(irq);
	spin_unlock_irqrestore(&cobalt_lock, flags);
	return 0;
}