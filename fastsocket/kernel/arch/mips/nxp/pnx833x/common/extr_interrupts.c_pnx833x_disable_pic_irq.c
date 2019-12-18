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

/* Variables and functions */
 int /*<<< orphan*/  IRQFLAG_DISABLED ; 
 unsigned int PNX833X_PIC_IRQ_BASE ; 
 int /*<<< orphan*/ * irqflags ; 
 int /*<<< orphan*/  pnx833x_hard_disable_pic_irq (unsigned int) ; 
 int /*<<< orphan*/  pnx833x_irq_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pnx833x_disable_pic_irq(unsigned int irq)
{
	unsigned long flags;
	unsigned int pic_irq = irq - PNX833X_PIC_IRQ_BASE;

	spin_lock_irqsave(&pnx833x_irq_lock, flags);

	irqflags[pic_irq] |= IRQFLAG_DISABLED;
	pnx833x_hard_disable_pic_irq(pic_irq);

	spin_unlock_irqrestore(&pnx833x_irq_lock, flags);
}