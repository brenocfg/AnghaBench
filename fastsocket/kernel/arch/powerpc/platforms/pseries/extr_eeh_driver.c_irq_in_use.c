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
struct irq_desc {int /*<<< orphan*/  lock; scalar_t__ action; } ;

/* Variables and functions */
 struct irq_desc* irq_desc ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int irq_in_use(unsigned int irq)
{
	int rc = 0;
	unsigned long flags;
   struct irq_desc *desc = irq_desc + irq;

	spin_lock_irqsave(&desc->lock, flags);
	if (desc->action)
		rc = 1;
	spin_unlock_irqrestore(&desc->lock, flags);
	return rc;
}