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

/* Variables and functions */
 int /*<<< orphan*/  octeon_irq_core_disable_local (unsigned int) ; 
 int /*<<< orphan*/  on_each_cpu (void (*) (void*),void*,int) ; 

__attribute__((used)) static void octeon_irq_core_disable(unsigned int irq)
{
#ifdef CONFIG_SMP
	on_each_cpu((void (*)(void *)) octeon_irq_core_disable_local,
		    (void *) (long) irq, 1);
#else
	octeon_irq_core_disable_local(irq);
#endif
}