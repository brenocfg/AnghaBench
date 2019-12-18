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
struct atl1c_hw {int dummy; } ;
struct atl1c_adapter {int /*<<< orphan*/  mdio_lock; struct atl1c_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  atl1c_restart_autoneg (struct atl1c_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void atl1c_phy_config(unsigned long data)
{
	struct atl1c_adapter *adapter = (struct atl1c_adapter *) data;
	struct atl1c_hw *hw = &adapter->hw;
	unsigned long flags;

	spin_lock_irqsave(&adapter->mdio_lock, flags);
	atl1c_restart_autoneg(hw);
	spin_unlock_irqrestore(&adapter->mdio_lock, flags);
}