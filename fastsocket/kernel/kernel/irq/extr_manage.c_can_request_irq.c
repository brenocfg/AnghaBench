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
struct irqaction {unsigned long flags; } ;
struct irq_desc {int status; struct irqaction* action; } ;

/* Variables and functions */
 unsigned long IRQF_SHARED ; 
 int IRQ_NOREQUEST ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 

int can_request_irq(unsigned int irq, unsigned long irqflags)
{
	struct irq_desc *desc = irq_to_desc(irq);
	struct irqaction *action;

	if (!desc)
		return 0;

	if (desc->status & IRQ_NOREQUEST)
		return 0;

	action = desc->action;
	if (action)
		if (irqflags & action->flags & IRQF_SHARED)
			action = NULL;

	return !action;
}