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
struct irq_desc {int /*<<< orphan*/ * affinity_notify; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __free_irq (unsigned int,void*) ; 
 int /*<<< orphan*/  chip_bus_lock (unsigned int,struct irq_desc*) ; 
 int /*<<< orphan*/  chip_bus_sync_unlock (unsigned int,struct irq_desc*) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void free_irq(unsigned int irq, void *dev_id)
{
	struct irq_desc *desc = irq_to_desc(irq);

	if (!desc)
		return;

#ifdef CONFIG_SMP
	if (WARN_ON(desc->affinity_notify))
		desc->affinity_notify = NULL;
#endif

	chip_bus_lock(irq, desc);
	kfree(__free_irq(irq, dev_id));
	chip_bus_sync_unlock(irq, desc);
}