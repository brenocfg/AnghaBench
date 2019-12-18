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
struct locomo {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ LOCOMO_GPO ; 
 struct locomo* dev_get_drvdata (struct device*) ; 
 unsigned int locomo_readl (scalar_t__) ; 
 int /*<<< orphan*/  locomo_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void locomo_gpio_write(struct device *dev, unsigned int bits, unsigned int set)
{
	struct locomo *lchip = dev_get_drvdata(dev);
	unsigned long flags;
	unsigned int r;

	if (!lchip)
		return;

	spin_lock_irqsave(&lchip->lock, flags);

	r = locomo_readl(lchip->base + LOCOMO_GPO);
	if (set)
		r |= bits;
	else
		r &= ~bits;
	locomo_writel(r, lchip->base + LOCOMO_GPO);

	spin_unlock_irqrestore(&lchip->lock, flags);
}