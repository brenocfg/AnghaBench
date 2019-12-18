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
struct irq_cfg {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int __assign_irq_vector (int,struct irq_cfg*,struct cpumask const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vector_lock ; 

int assign_irq_vector(int irq, struct irq_cfg *cfg, const struct cpumask *mask)
{
	int err;
	unsigned long flags;

	spin_lock_irqsave(&vector_lock, flags);
	err = __assign_irq_vector(irq, cfg, mask);
	spin_unlock_irqrestore(&vector_lock, flags);
	return err;
}