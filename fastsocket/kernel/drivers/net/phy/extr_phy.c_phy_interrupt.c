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
struct phy_device {scalar_t__ state; int /*<<< orphan*/  phy_queue; int /*<<< orphan*/  irq_disable; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PHY_HALTED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t phy_interrupt(int irq, void *phy_dat)
{
	struct phy_device *phydev = phy_dat;

	if (PHY_HALTED == phydev->state)
		return IRQ_NONE;		/* It can't be ours.  */

	/* The MDIO bus is not allowed to be written in interrupt
	 * context, so we need to disable the irq here.  A work
	 * queue will write the PHY to disable and clear the
	 * interrupt, and then reenable the irq line. */
	disable_irq_nosync(irq);
	atomic_inc(&phydev->irq_disable);

	schedule_work(&phydev->phy_queue);

	return IRQ_HANDLED;
}