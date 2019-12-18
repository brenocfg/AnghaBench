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
struct irq_desc {scalar_t__ wake_depth; int /*<<< orphan*/  lock; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKEUP ; 
 int /*<<< orphan*/  WARN (int,char*,unsigned int) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int set_irq_wake_real (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int set_irq_wake(unsigned int irq, unsigned int on)
{
	struct irq_desc *desc = irq_to_desc(irq);
	unsigned long flags;
	int ret = 0;

	/* wakeup-capable irqs can be shared between drivers that
	 * don't need to have the same sleep mode behaviors.
	 */
	spin_lock_irqsave(&desc->lock, flags);
	if (on) {
		if (desc->wake_depth++ == 0) {
			ret = set_irq_wake_real(irq, on);
			if (ret)
				desc->wake_depth = 0;
			else
				desc->status |= IRQ_WAKEUP;
		}
	} else {
		if (desc->wake_depth == 0) {
			WARN(1, "Unbalanced IRQ %d wake disable\n", irq);
		} else if (--desc->wake_depth == 0) {
			ret = set_irq_wake_real(irq, on);
			if (ret)
				desc->wake_depth = 1;
			else
				desc->status &= ~IRQ_WAKEUP;
		}
	}

	spin_unlock_irqrestore(&desc->lock, flags);
	return ret;
}