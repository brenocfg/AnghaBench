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
struct phy_device {scalar_t__ state; scalar_t__ irq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ PHY_HALTED ; 
 int /*<<< orphan*/  PHY_INTERRUPT_DISABLED ; 
 scalar_t__ PHY_POLL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_clear_interrupt (struct phy_device*) ; 
 int /*<<< orphan*/  phy_config_interrupt (struct phy_device*,int /*<<< orphan*/ ) ; 

void phy_stop(struct phy_device *phydev)
{
	mutex_lock(&phydev->lock);

	if (PHY_HALTED == phydev->state)
		goto out_unlock;

	if (phydev->irq != PHY_POLL) {
		/* Disable PHY Interrupts */
		phy_config_interrupt(phydev, PHY_INTERRUPT_DISABLED);

		/* Clear any pending interrupts */
		phy_clear_interrupt(phydev);
	}

	phydev->state = PHY_HALTED;

out_unlock:
	mutex_unlock(&phydev->lock);

	/*
	 * Cannot call flush_scheduled_work() here as desired because
	 * of rtnl_lock(), but PHY_HALTED shall guarantee phy_change()
	 * will not reenable interrupts.
	 */
}