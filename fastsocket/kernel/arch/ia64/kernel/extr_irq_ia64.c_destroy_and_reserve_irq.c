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
 int /*<<< orphan*/  IRQ_RSVD ; 
 int /*<<< orphan*/  __clear_irq_vector (unsigned int) ; 
 int /*<<< orphan*/  dynamic_irq_cleanup (unsigned int) ; 
 int /*<<< orphan*/ * irq_status ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vector_lock ; 

void destroy_and_reserve_irq(unsigned int irq)
{
	unsigned long flags;

	dynamic_irq_cleanup(irq);

	spin_lock_irqsave(&vector_lock, flags);
	__clear_irq_vector(irq);
	irq_status[irq] = IRQ_RSVD;
	spin_unlock_irqrestore(&vector_lock, flags);
}