#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mask_clear; } ;
struct TYPE_3__ {int /*<<< orphan*/  clear; } ;

/* Variables and functions */
 unsigned long SUN4M_INT_FLOPPY ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  sbus_writel (unsigned long,int /*<<< orphan*/ *) ; 
 int smp_processor_id () ; 
 unsigned long sun4m_get_irqmask (unsigned int) ; 
 TYPE_2__* sun4m_irq_global ; 
 TYPE_1__** sun4m_irq_percpu ; 

__attribute__((used)) static void sun4m_enable_irq(unsigned int irq_nr)
{
	unsigned long mask, flags;
	int cpu = smp_processor_id();

	/* Dreadful floppy hack. When we use 0x2b instead of
         * 0x0b the system blows (it starts to whistle!).
         * So we continue to use 0x0b. Fixme ASAP. --P3
         */
        if (irq_nr != 0x0b) {
		mask = sun4m_get_irqmask(irq_nr);
		local_irq_save(flags);
		if (irq_nr > 15)
			sbus_writel(mask, &sun4m_irq_global->mask_clear);
		else
			sbus_writel(mask, &sun4m_irq_percpu[cpu]->clear);
		local_irq_restore(flags);    
	} else {
		local_irq_save(flags);
		sbus_writel(SUN4M_INT_FLOPPY, &sun4m_irq_global->mask_clear);
		local_irq_restore(flags);
	}
}