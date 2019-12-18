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
struct phy_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  irq_disable; int /*<<< orphan*/  phy_queue; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct phy_device*) ; 
 int phy_disable_interrupts (struct phy_device*) ; 
 int /*<<< orphan*/  phy_error (struct phy_device*) ; 

int phy_stop_interrupts(struct phy_device *phydev)
{
	int err;

	err = phy_disable_interrupts(phydev);

	if (err)
		phy_error(phydev);

	free_irq(phydev->irq, phydev);

	/*
	 * Cannot call flush_scheduled_work() here as desired because
	 * of rtnl_lock(), but we do not really care about what would
	 * be done, except from enable_irq(), so cancel any work
	 * possibly pending and take care of the matter below.
	 */
	cancel_work_sync(&phydev->phy_queue);
	/*
	 * If work indeed has been cancelled, disable_irq() will have
	 * been left unbalanced from phy_interrupt() and enable_irq()
	 * has to be called so that other devices on the line work.
	 */
	while (atomic_dec_return(&phydev->irq_disable) >= 0)
		enable_irq(phydev->irq);

	return err;
}