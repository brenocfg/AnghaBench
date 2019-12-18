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
struct sm501_devdata {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  dev; scalar_t__ regs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SM501_MISC_CONTROL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long) ; 
 struct sm501_devdata* dev_get_drvdata (struct device*) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  sm501_sync_regs (struct sm501_devdata*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

int sm501_misc_control(struct device *dev,
		       unsigned long set, unsigned long clear)
{
	struct sm501_devdata *sm = dev_get_drvdata(dev);
	unsigned long misc;
	unsigned long save;
	unsigned long to;

	spin_lock_irqsave(&sm->reg_lock, save);

	misc = readl(sm->regs + SM501_MISC_CONTROL);
	to = (misc & ~clear) | set;

	if (to != misc) {
		writel(to, sm->regs + SM501_MISC_CONTROL);
		sm501_sync_regs(sm);

		dev_dbg(sm->dev, "MISC_CONTROL %08lx\n", misc);
	}

	spin_unlock_irqrestore(&sm->reg_lock, save);
	return to;
}