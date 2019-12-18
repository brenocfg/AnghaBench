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
struct inf_hw {int /*<<< orphan*/  lock; int /*<<< orphan*/  ipac; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  irqloops ; 
 int /*<<< orphan*/  mISDNipac_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
gazel_irq(int intno, void *dev_id)
{
	struct inf_hw *hw = dev_id;
	irqreturn_t ret;

	spin_lock(&hw->lock);
	ret = mISDNipac_irq(&hw->ipac, irqloops);
	spin_unlock(&hw->lock);
	return ret;
}