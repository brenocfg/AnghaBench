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
struct irq_desc {unsigned int irq; struct irq_cfg* chip_data; } ;
struct irq_cfg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __eoi_ioapic_irq (unsigned int,struct irq_cfg*) ; 
 int /*<<< orphan*/  ioapic_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void eoi_ioapic_irq(struct irq_desc *desc)
{
	struct irq_cfg *cfg;
	unsigned long flags;
	unsigned int irq;

	irq = desc->irq;
	cfg = desc->chip_data;

	spin_lock_irqsave(&ioapic_lock, flags);
	__eoi_ioapic_irq(irq, cfg);
	spin_unlock_irqrestore(&ioapic_lock, flags);
}