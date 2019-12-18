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
struct TYPE_2__ {int cpu; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int CPU_FIXED ; 
 int FIRST_IRQ ; 
 scalar_t__ cpu_isset (int,int /*<<< orphan*/ ) ; 
 int first_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* irq_allocations ; 
 int /*<<< orphan*/  irq_lock ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int irq_cpu(int irq)
{
	int cpu;
        unsigned long flags;

        spin_lock_irqsave(&irq_lock, flags);
        cpu = irq_allocations[irq - FIRST_IRQ].cpu;

	/* Fixed interrupts stay on the local CPU. */
	if (cpu == CPU_FIXED)
        {
		spin_unlock_irqrestore(&irq_lock, flags);
		return smp_processor_id();
        }


	/* Let the interrupt stay if possible */
	if (cpu_isset(cpu, irq_allocations[irq - FIRST_IRQ].mask))
		goto out;

	/* IRQ must be moved to another CPU. */
	cpu = first_cpu(irq_allocations[irq - FIRST_IRQ].mask);
	irq_allocations[irq - FIRST_IRQ].cpu = cpu;
out:
	spin_unlock_irqrestore(&irq_lock, flags);
	return cpu;
}