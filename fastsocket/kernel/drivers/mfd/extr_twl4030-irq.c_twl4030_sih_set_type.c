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
struct sih_agent {unsigned int irq_base; int /*<<< orphan*/  edge_work; int /*<<< orphan*/  edge_change; } ;
struct irq_desc {unsigned int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 struct sih_agent* get_irq_chip_data (unsigned int) ; 
 struct irq_desc* irq_to_desc (unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sih_agent_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static int twl4030_sih_set_type(unsigned irq, unsigned trigger)
{
	struct sih_agent *sih = get_irq_chip_data(irq);
	struct irq_desc *desc = irq_to_desc(irq);
	unsigned long flags;

	if (!desc) {
		pr_err("twl4030: Invalid IRQ: %d\n", irq);
		return -EINVAL;
	}

	if (trigger & ~(IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		return -EINVAL;

	spin_lock_irqsave(&sih_agent_lock, flags);
	if ((desc->status & IRQ_TYPE_SENSE_MASK) != trigger) {
		desc->status &= ~IRQ_TYPE_SENSE_MASK;
		desc->status |= trigger;
		sih->edge_change |= BIT(irq - sih->irq_base);
		queue_work(wq, &sih->edge_work);
	}
	spin_unlock_irqrestore(&sih_agent_lock, flags);
	return 0;
}