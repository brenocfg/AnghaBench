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
struct pt_regs {int dummy; } ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_handle_irq_desc (unsigned int,struct irq_desc*) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  stack_overflow_check (struct pt_regs*) ; 
 scalar_t__ unlikely (int) ; 

bool handle_irq(unsigned irq, struct pt_regs *regs)
{
	struct irq_desc *desc;

	stack_overflow_check(regs);

	desc = irq_to_desc(irq);
	if (unlikely(!desc))
		return false;

	generic_handle_irq_desc(irq, desc);
	return true;
}