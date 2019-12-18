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
struct cpumask {int dummy; } ;
struct TYPE_2__ {struct cpumask mask; } ;

/* Variables and functions */
 unsigned int FIRST_IRQ ; 
 TYPE_1__* irq_allocations ; 
 int /*<<< orphan*/  irq_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int set_affinity_crisv32_irq(unsigned int irq, const struct cpumask *dest)
{
	unsigned long flags;
	spin_lock_irqsave(&irq_lock, flags);
	irq_allocations[irq - FIRST_IRQ].mask = *dest;
	spin_unlock_irqrestore(&irq_lock, flags);

	return 0;
}