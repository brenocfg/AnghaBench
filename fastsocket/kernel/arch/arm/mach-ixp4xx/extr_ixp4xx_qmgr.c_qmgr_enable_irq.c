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
struct TYPE_2__ {int /*<<< orphan*/ * irqen; } ;

/* Variables and functions */
 int HALF_QUEUES ; 
 int __raw_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmgr_lock ; 
 TYPE_1__* qmgr_regs ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void qmgr_enable_irq(unsigned int queue)
{
	unsigned long flags;
	int half = queue / 32;
	u32 mask = 1 << (queue & (HALF_QUEUES - 1));

	spin_lock_irqsave(&qmgr_lock, flags);
	__raw_writel(__raw_readl(&qmgr_regs->irqen[half]) | mask,
		     &qmgr_regs->irqen[half]);
	spin_unlock_irqrestore(&qmgr_lock, flags);
}