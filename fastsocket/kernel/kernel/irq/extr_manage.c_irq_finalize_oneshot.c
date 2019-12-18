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
struct irq_desc {int status; int /*<<< orphan*/  lock; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmask ) (unsigned int) ;} ;

/* Variables and functions */
 int IRQ_DISABLED ; 
 int IRQ_MASKED ; 
 int /*<<< orphan*/  chip_bus_lock (unsigned int,struct irq_desc*) ; 
 int /*<<< orphan*/  chip_bus_sync_unlock (unsigned int,struct irq_desc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 

__attribute__((used)) static void irq_finalize_oneshot(unsigned int irq, struct irq_desc *desc)
{
	chip_bus_lock(irq, desc);
	spin_lock_irq(&desc->lock);
	if (!(desc->status & IRQ_DISABLED) && (desc->status & IRQ_MASKED)) {
		desc->status &= ~IRQ_MASKED;
		desc->chip->unmask(irq);
	}
	spin_unlock_irq(&desc->lock);
	chip_bus_sync_unlock(irq, desc);
}