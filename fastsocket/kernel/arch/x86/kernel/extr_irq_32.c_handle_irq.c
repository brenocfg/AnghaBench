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
struct irq_desc {int /*<<< orphan*/  (* handle_irq ) (unsigned int,struct irq_desc*) ;} ;

/* Variables and functions */
 int check_stack_overflow () ; 
 int /*<<< orphan*/  execute_on_irq_stack (int,struct irq_desc*,unsigned int) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  print_stack_overflow () ; 
 int /*<<< orphan*/  stub1 (unsigned int,struct irq_desc*) ; 
 scalar_t__ unlikely (int) ; 

bool handle_irq(unsigned irq, struct pt_regs *regs)
{
	struct irq_desc *desc;
	int overflow;

	overflow = check_stack_overflow();

	desc = irq_to_desc(irq);
	if (unlikely(!desc))
		return false;

	if (!execute_on_irq_stack(overflow, desc, irq)) {
		if (unlikely(overflow))
			print_stack_overflow();
		desc->handle_irq(irq, desc);
	}

	return true;
}