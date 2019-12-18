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
struct TYPE_2__ {scalar_t__ start; } ;
struct inf_hw {int /*<<< orphan*/  lock; int /*<<< orphan*/  ipac; int /*<<< orphan*/  irqcnt; TYPE_1__ cfg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int NICCY_IRQ_BIT ; 
 int NICCY_IRQ_CTRL_REG ; 
 int inl (int) ; 
 int /*<<< orphan*/  irqloops ; 
 int /*<<< orphan*/  mISDNipac_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
niccy_irq(int intno, void *dev_id)
{
	struct inf_hw *hw = dev_id;
	u32 val;

	spin_lock(&hw->lock);
	val = inl((u32)hw->cfg.start + NICCY_IRQ_CTRL_REG);
	if (!(val & NICCY_IRQ_BIT)) { /* for us or shared ? */
		spin_unlock(&hw->lock);
		return IRQ_NONE; /* shared */
	}
	outl(val, (u32)hw->cfg.start + NICCY_IRQ_CTRL_REG);
	hw->irqcnt++;
	mISDNipac_irq(&hw->ipac, irqloops);
	spin_unlock(&hw->lock);
	return IRQ_HANDLED;
}