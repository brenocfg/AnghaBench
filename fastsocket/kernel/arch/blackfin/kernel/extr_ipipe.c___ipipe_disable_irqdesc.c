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
struct ipipe_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ *) ; 
 int __ipipe_get_irq_priority (unsigned int) ; 
 int /*<<< orphan*/ * __ipipe_irq_lvdepth ; 
 int /*<<< orphan*/  __ipipe_irq_lvmask ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct ipipe_domain ipipe_root ; 

void __ipipe_disable_irqdesc(struct ipipe_domain *ipd, unsigned irq)
{
	int prio = __ipipe_get_irq_priority(irq);

	if (ipd != &ipipe_root &&
	    atomic_dec_and_test(&__ipipe_irq_lvdepth[prio]))
		__clear_bit(prio, &__ipipe_irq_lvmask);
}