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
struct TYPE_4__ {int /*<<< orphan*/ * irqs; } ;
struct TYPE_3__ {int /*<<< orphan*/ * irqs; } ;
struct z8530_dev {int /*<<< orphan*/  lock; TYPE_2__ chanA; TYPE_1__ chanB; } ;

/* Variables and functions */
 int /*<<< orphan*/  R9 ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_zsreg (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  z8530_nop ; 

int z8530_shutdown(struct z8530_dev *dev)
{
	unsigned long flags;
	/* Reset the chip */

	spin_lock_irqsave(&dev->lock, flags);
	dev->chanA.irqs=&z8530_nop;
	dev->chanB.irqs=&z8530_nop;
	write_zsreg(&dev->chanA, R9, 0xC0);
	/* We must lock the udelay, the chip is offlimits here */
	udelay(100);
	spin_unlock_irqrestore(&dev->lock, flags);
	return 0;
}