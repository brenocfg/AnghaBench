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
struct TYPE_2__ {int /*<<< orphan*/  action; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xen_register_percpu_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int saved_irq_cnt ; 
 TYPE_1__* saved_percpu_irqs ; 

void xen_smp_intr_init_early(unsigned int cpu)
{
#ifdef CONFIG_SMP
	unsigned int i;

	for (i = 0; i < saved_irq_cnt; i++)
		__xen_register_percpu_irq(cpu, saved_percpu_irqs[i].irq,
					  saved_percpu_irqs[i].action, 0);
#endif
}