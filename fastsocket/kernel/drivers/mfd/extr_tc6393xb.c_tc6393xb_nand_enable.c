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
struct tc6393xb {int /*<<< orphan*/  lock; scalar_t__ scr; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ SCR_GPI_BCR (int) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 struct tc6393xb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int,scalar_t__) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tc6393xb_nand_enable(struct platform_device *nand)
{
	struct platform_device *dev = to_platform_device(nand->dev.parent);
	struct tc6393xb *tc6393xb = platform_get_drvdata(dev);
	unsigned long flags;

	spin_lock_irqsave(&tc6393xb->lock, flags);

	/* SMD buffer on */
	dev_dbg(&dev->dev, "SMD buffer on\n");
	tmio_iowrite8(0xff, tc6393xb->scr + SCR_GPI_BCR(1));

	spin_unlock_irqrestore(&tc6393xb->lock, flags);

	return 0;
}