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

/* Variables and functions */
 scalar_t__ UIC_ER ; 
 struct uic* get_irq_chip_data (unsigned int) ; 
 int mfdcr (scalar_t__) ; 
 int /*<<< orphan*/  mtdcr (scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int uic_irq_to_hw (unsigned int) ; 

__attribute__((used)) static void uic_mask_irq(unsigned int virq)
{
	struct uic *uic = get_irq_chip_data(virq);
	unsigned int src = uic_irq_to_hw(virq);
	unsigned long flags;
	u32 er;

	spin_lock_irqsave(&uic->lock, flags);
	er = mfdcr(uic->dcrbase + UIC_ER);
	er &= ~(1 << (31 - src));
	mtdcr(uic->dcrbase + UIC_ER, er);
	spin_unlock_irqrestore(&uic->lock, flags);
}