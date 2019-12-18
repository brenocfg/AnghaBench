#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct irq_desc {int status; int /*<<< orphan*/  lock; TYPE_1__* chip; } ;
struct TYPE_4__ {int /*<<< orphan*/  irqhost; scalar_t__ regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unmask ) (unsigned int) ;int /*<<< orphan*/  (* ack ) (unsigned int) ;int /*<<< orphan*/  (* mask ) (unsigned int) ;} ;

/* Variables and functions */
 int IRQ_DISABLED ; 
 scalar_t__ MEDIA5200_IRQ_ENABLE ; 
 int MEDIA5200_IRQ_SHIFT ; 
 scalar_t__ MEDIA5200_IRQ_STATUS ; 
 int ffs (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int in_be32 (scalar_t__) ; 
 int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ media5200_irq ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 
 int /*<<< orphan*/  stub3 (unsigned int) ; 

void media5200_irq_cascade(unsigned int virq, struct irq_desc *desc)
{
	int sub_virq, val;
	u32 status, enable;

	/* Mask off the cascaded IRQ */
	spin_lock(&desc->lock);
	desc->chip->mask(virq);
	spin_unlock(&desc->lock);

	/* Ask the FPGA for IRQ status.  If 'val' is 0, then no irqs
	 * are pending.  'ffs()' is 1 based */
	status = in_be32(media5200_irq.regs + MEDIA5200_IRQ_ENABLE);
	enable = in_be32(media5200_irq.regs + MEDIA5200_IRQ_STATUS);
	val = ffs((status & enable) >> MEDIA5200_IRQ_SHIFT);
	if (val) {
		sub_virq = irq_linear_revmap(media5200_irq.irqhost, val - 1);
		/* pr_debug("%s: virq=%i s=%.8x e=%.8x hwirq=%i subvirq=%i\n",
		 *          __func__, virq, status, enable, val - 1, sub_virq);
		 */
		generic_handle_irq(sub_virq);
	}

	/* Processing done; can reenable the cascade now */
	spin_lock(&desc->lock);
	desc->chip->ack(virq);
	if (!(desc->status & IRQ_DISABLED))
		desc->chip->unmask(virq);
	spin_unlock(&desc->lock);
}