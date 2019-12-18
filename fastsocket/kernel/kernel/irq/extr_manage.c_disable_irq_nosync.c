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
struct irq_desc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __disable_irq (struct irq_desc*,unsigned int,int) ; 
 int /*<<< orphan*/  chip_bus_lock (unsigned int,struct irq_desc*) ; 
 int /*<<< orphan*/  chip_bus_sync_unlock (unsigned int,struct irq_desc*) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void disable_irq_nosync(unsigned int irq)
{
	struct irq_desc *desc = irq_to_desc(irq);
	unsigned long flags;

	if (!desc)
		return;

	chip_bus_lock(irq, desc);
	spin_lock_irqsave(&desc->lock, flags);
	__disable_irq(desc, irq, false);
	spin_unlock_irqrestore(&desc->lock, flags);
	chip_bus_sync_unlock(irq, desc);
}