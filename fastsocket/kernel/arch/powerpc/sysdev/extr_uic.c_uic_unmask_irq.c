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
typedef  int u32 ;
struct uic {int /*<<< orphan*/  lock; scalar_t__ dcrbase; } ;
struct irq_desc {int status; } ;

/* Variables and functions */
 int IRQ_LEVEL ; 
 scalar_t__ UIC_ER ; 
 scalar_t__ UIC_SR ; 
 struct uic* get_irq_chip_data (unsigned int) ; 
 struct irq_desc* get_irq_desc (unsigned int) ; 
 int mfdcr (scalar_t__) ; 
 int /*<<< orphan*/  mtdcr (scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int uic_irq_to_hw (unsigned int) ; 

__attribute__((used)) static void uic_unmask_irq(unsigned int virq)
{
	struct irq_desc *desc = get_irq_desc(virq);
	struct uic *uic = get_irq_chip_data(virq);
	unsigned int src = uic_irq_to_hw(virq);
	unsigned long flags;
	u32 er, sr;

	sr = 1 << (31-src);
	spin_lock_irqsave(&uic->lock, flags);
	/* ack level-triggered interrupts here */
	if (desc->status & IRQ_LEVEL)
		mtdcr(uic->dcrbase + UIC_SR, sr);
	er = mfdcr(uic->dcrbase + UIC_ER);
	er |= sr;
	mtdcr(uic->dcrbase + UIC_ER, er);
	spin_unlock_irqrestore(&uic->lock, flags);
}