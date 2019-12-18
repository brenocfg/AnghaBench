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
struct asic3 {unsigned int irq_base; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int ASIC3_INTMASK_MASK0 ; 
 scalar_t__ ASIC3_INTR_BASE ; 
 scalar_t__ ASIC3_INTR_INT_MASK ; 
 unsigned int ASIC3_NUM_GPIOS ; 
 int asic3_read_register (struct asic3*,scalar_t__) ; 
 int /*<<< orphan*/  asic3_write_register (struct asic3*,scalar_t__,int) ; 
 struct asic3* get_irq_chip_data (unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void asic3_unmask_irq(unsigned int irq)
{
	struct asic3 *asic = get_irq_chip_data(irq);
	int regval;
	unsigned long flags;

	spin_lock_irqsave(&asic->lock, flags);
	regval = asic3_read_register(asic,
				     ASIC3_INTR_BASE +
				     ASIC3_INTR_INT_MASK);

	regval |= (ASIC3_INTMASK_MASK0 <<
		   (irq - (asic->irq_base + ASIC3_NUM_GPIOS)));

	asic3_write_register(asic,
			     ASIC3_INTR_BASE +
			     ASIC3_INTR_INT_MASK,
			     regval);
	spin_unlock_irqrestore(&asic->lock, flags);
}