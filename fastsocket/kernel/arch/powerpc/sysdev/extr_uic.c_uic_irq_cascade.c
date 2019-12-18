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
typedef  int /*<<< orphan*/  u32 ;
struct uic {int /*<<< orphan*/  irqhost; scalar_t__ dcrbase; } ;
struct irq_desc {int status; int /*<<< orphan*/  lock; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmask ) (unsigned int) ;int /*<<< orphan*/  (* ack ) (unsigned int) ;int /*<<< orphan*/  (* mask_ack ) (unsigned int) ;int /*<<< orphan*/  (* mask ) (unsigned int) ;} ;

/* Variables and functions */
 int IRQ_DISABLED ; 
 int IRQ_LEVEL ; 
 scalar_t__ UIC_MSR ; 
 int ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 struct uic* get_irq_data (unsigned int) ; 
 int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mfdcr (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 
 int /*<<< orphan*/  stub3 (unsigned int) ; 
 int /*<<< orphan*/  stub4 (unsigned int) ; 

void uic_irq_cascade(unsigned int virq, struct irq_desc *desc)
{
	struct uic *uic = get_irq_data(virq);
	u32 msr;
	int src;
	int subvirq;

	spin_lock(&desc->lock);
	if (desc->status & IRQ_LEVEL)
		desc->chip->mask(virq);
	else
		desc->chip->mask_ack(virq);
	spin_unlock(&desc->lock);

	msr = mfdcr(uic->dcrbase + UIC_MSR);
	if (!msr) /* spurious interrupt */
		goto uic_irq_ret;

	src = 32 - ffs(msr);

	subvirq = irq_linear_revmap(uic->irqhost, src);
	generic_handle_irq(subvirq);

uic_irq_ret:
	spin_lock(&desc->lock);
	if (desc->status & IRQ_LEVEL)
		desc->chip->ack(virq);
	if (!(desc->status & IRQ_DISABLED) && desc->chip->unmask)
		desc->chip->unmask(virq);
	spin_unlock(&desc->lock);
}