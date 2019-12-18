#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct irq_desc {int status; TYPE_1__* chip; } ;
struct TYPE_5__ {int (* get_irq ) (unsigned int) ;} ;
typedef  TYPE_2__ irq_cascade_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* unmask ) (unsigned int) ;int /*<<< orphan*/  (* ack ) (unsigned int) ;int /*<<< orphan*/  (* mask ) (unsigned int) ;int /*<<< orphan*/  (* mask_ack ) (unsigned int) ;} ;

/* Variables and functions */
 int IRQ_DISABLED ; 
 unsigned int NR_IRQS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_IRQ (unsigned int) ; 
 TYPE_2__* irq_cascade ; 
 struct irq_desc* irq_desc ; 
 int /*<<< orphan*/  irq_err_count ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 
 int /*<<< orphan*/  stub3 (unsigned int) ; 
 int stub4 (unsigned int) ; 
 int /*<<< orphan*/  stub5 (unsigned int) ; 

__attribute__((used)) static void irq_dispatch(unsigned int irq)
{
	irq_cascade_t *cascade;
	struct irq_desc *desc;

	if (irq >= NR_IRQS) {
		atomic_inc(&irq_err_count);
		return;
	}

	cascade = irq_cascade + irq;
	if (cascade->get_irq != NULL) {
		unsigned int source_irq = irq;
		int ret;
		desc = irq_desc + source_irq;
		if (desc->chip->mask_ack)
			desc->chip->mask_ack(source_irq);
		else {
			desc->chip->mask(source_irq);
			desc->chip->ack(source_irq);
		}
		ret = cascade->get_irq(irq);
		irq = ret;
		if (ret < 0)
			atomic_inc(&irq_err_count);
		else
			irq_dispatch(irq);
		if (!(desc->status & IRQ_DISABLED) && desc->chip->unmask)
			desc->chip->unmask(source_irq);
	} else
		do_IRQ(irq);
}