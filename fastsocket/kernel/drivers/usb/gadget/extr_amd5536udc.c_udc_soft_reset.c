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
struct udc {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  cfg; int /*<<< orphan*/  irqsts; int /*<<< orphan*/  ep_irqsts; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (struct udc*,char*) ; 
 int /*<<< orphan*/  UDC_DEVCFG_SOFTRESET ; 
 int /*<<< orphan*/  UDC_DEV_MSK_DISABLE ; 
 int /*<<< orphan*/  UDC_EPINT_MSK_DISABLE_ALL ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udc_irq_spinlock ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void udc_soft_reset(struct udc *dev)
{
	unsigned long	flags;

	DBG(dev, "Soft reset\n");
	/*
	 * reset possible waiting interrupts, because int.
	 * status is lost after soft reset,
	 * ep int. status reset
	 */
	writel(UDC_EPINT_MSK_DISABLE_ALL, &dev->regs->ep_irqsts);
	/* device int. status reset */
	writel(UDC_DEV_MSK_DISABLE, &dev->regs->irqsts);

	spin_lock_irqsave(&udc_irq_spinlock, flags);
	writel(AMD_BIT(UDC_DEVCFG_SOFTRESET), &dev->regs->cfg);
	readl(&dev->regs->cfg);
	spin_unlock_irqrestore(&udc_irq_spinlock, flags);

}