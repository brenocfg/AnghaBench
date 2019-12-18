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
struct irqaction {int dummy; } ;
struct irq_desc {int /*<<< orphan*/ * chip; int /*<<< orphan*/  status; } ;
typedef  unsigned int ia64_vector ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_MASK_ALL ; 
 int /*<<< orphan*/  IRQ_PER_CPU ; 
 int /*<<< orphan*/  bind_irq_vector (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 struct irq_desc* irq_desc ; 
 int /*<<< orphan*/  irq_type_ia64_lsapic ; 
 int /*<<< orphan*/  setup_irq (unsigned int,struct irqaction*) ; 

void
ia64_native_register_percpu_irq (ia64_vector vec, struct irqaction *action)
{
	struct irq_desc *desc;
	unsigned int irq;

	irq = vec;
	BUG_ON(bind_irq_vector(irq, vec, CPU_MASK_ALL));
	desc = irq_desc + irq;
	desc->status |= IRQ_PER_CPU;
	desc->chip = &irq_type_ia64_lsapic;
	if (action)
		setup_irq(irq, action);
}