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
struct irq_desc {scalar_t__ depth; } ;
struct ipipe_domain {int dummy; } ;

/* Variables and functions */
 int __ipipe_get_irq_priority (unsigned int) ; 
 int /*<<< orphan*/ * __ipipe_irq_lvdepth ; 
 int /*<<< orphan*/  __ipipe_irq_lvmask ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 struct ipipe_domain ipipe_root ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 

void __ipipe_enable_irqdesc(struct ipipe_domain *ipd, unsigned irq)
{
	struct irq_desc *desc = irq_to_desc(irq);
	int prio = __ipipe_get_irq_priority(irq);

	desc->depth = 0;
	if (ipd != &ipipe_root &&
	    atomic_inc_return(&__ipipe_irq_lvdepth[prio]) == 1)
		__set_bit(prio, &__ipipe_irq_lvmask);
}