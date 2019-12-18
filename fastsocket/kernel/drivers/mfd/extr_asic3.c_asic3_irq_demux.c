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
typedef  int u32 ;
struct irq_desc {int /*<<< orphan*/  (* handle_irq ) (int,struct irq_desc*) ;struct asic3* handler_data; TYPE_1__* chip; } ;
struct asic3 {int irq_base; int* irq_bothedge; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ack ) (unsigned int) ;} ;

/* Variables and functions */
 int ASIC3_GPIOS_PER_BANK ; 
 int ASIC3_GPIO_A_BASE ; 
 int ASIC3_GPIO_BASE_INCR ; 
 scalar_t__ ASIC3_GPIO_INT_STATUS ; 
 int ASIC3_NR_IRQS ; 
 int ASIC3_NUM_GPIOS ; 
 int ASIC3_NUM_GPIO_BANKS ; 
 scalar_t__ ASIC3_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTR ; 
 int MAX_ASIC_ISR_LOOPS ; 
 int /*<<< orphan*/  P_INT_STAT ; 
 int /*<<< orphan*/  asic3_irq_flip_edge (struct asic3*,unsigned long,int) ; 
 void* asic3_read_register (struct asic3*,scalar_t__) ; 
 int /*<<< orphan*/  asic3_write_register (struct asic3*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct irq_desc* irq_to_desc (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int,struct irq_desc*) ; 
 int /*<<< orphan*/  stub3 (int,struct irq_desc*) ; 

__attribute__((used)) static void asic3_irq_demux(unsigned int irq, struct irq_desc *desc)
{
	int iter, i;
	unsigned long flags;
	struct asic3 *asic;

	desc->chip->ack(irq);

	asic = desc->handler_data;

	for (iter = 0 ; iter < MAX_ASIC_ISR_LOOPS; iter++) {
		u32 status;
		int bank;

		spin_lock_irqsave(&asic->lock, flags);
		status = asic3_read_register(asic,
					     ASIC3_OFFSET(INTR, P_INT_STAT));
		spin_unlock_irqrestore(&asic->lock, flags);

		/* Check all ten register bits */
		if ((status & 0x3ff) == 0)
			break;

		/* Handle GPIO IRQs */
		for (bank = 0; bank < ASIC3_NUM_GPIO_BANKS; bank++) {
			if (status & (1 << bank)) {
				unsigned long base, istat;

				base = ASIC3_GPIO_A_BASE
				       + bank * ASIC3_GPIO_BASE_INCR;

				spin_lock_irqsave(&asic->lock, flags);
				istat = asic3_read_register(asic,
							    base +
							    ASIC3_GPIO_INT_STATUS);
				/* Clearing IntStatus */
				asic3_write_register(asic,
						     base +
						     ASIC3_GPIO_INT_STATUS, 0);
				spin_unlock_irqrestore(&asic->lock, flags);

				for (i = 0; i < ASIC3_GPIOS_PER_BANK; i++) {
					int bit = (1 << i);
					unsigned int irqnr;

					if (!(istat & bit))
						continue;

					irqnr = asic->irq_base +
						(ASIC3_GPIOS_PER_BANK * bank)
						+ i;
					desc = irq_to_desc(irqnr);
					desc->handle_irq(irqnr, desc);
					if (asic->irq_bothedge[bank] & bit)
						asic3_irq_flip_edge(asic, base,
								    bit);
				}
			}
		}

		/* Handle remaining IRQs in the status register */
		for (i = ASIC3_NUM_GPIOS; i < ASIC3_NR_IRQS; i++) {
			/* They start at bit 4 and go up */
			if (status & (1 << (i - ASIC3_NUM_GPIOS + 4))) {
				desc = irq_to_desc(asic->irq_base + i);
				desc->handle_irq(asic->irq_base + i,
						 desc);
			}
		}
	}

	if (iter >= MAX_ASIC_ISR_LOOPS)
		dev_err(asic->dev, "interrupt processing overrun\n");
}