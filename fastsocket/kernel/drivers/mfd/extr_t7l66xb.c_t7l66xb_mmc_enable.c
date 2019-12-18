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
typedef  int /*<<< orphan*/  u8 ;
struct t7l66xb {int /*<<< orphan*/  lock; scalar_t__ scr; int /*<<< orphan*/  clk32k; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ SCR_DEV_CTL ; 
 int /*<<< orphan*/  SCR_DEV_CTL_MMC ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct t7l66xb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmio_ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int t7l66xb_mmc_enable(struct platform_device *mmc)
{
	struct platform_device *dev = to_platform_device(mmc->dev.parent);
	struct t7l66xb *t7l66xb = platform_get_drvdata(dev);
	unsigned long flags;
	u8 dev_ctl;

	clk_enable(t7l66xb->clk32k);

	spin_lock_irqsave(&t7l66xb->lock, flags);

	dev_ctl = tmio_ioread8(t7l66xb->scr + SCR_DEV_CTL);
	dev_ctl |= SCR_DEV_CTL_MMC;
	tmio_iowrite8(dev_ctl, t7l66xb->scr + SCR_DEV_CTL);

	spin_unlock_irqrestore(&t7l66xb->lock, flags);

	return 0;
}