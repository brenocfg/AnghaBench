#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int global_device_reset; } ;
struct TYPE_6__ {TYPE_2__ _82575; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_3__ dev_spec; TYPE_1__ mac; } ;
struct igb_adapter {int eims_enable_mask; int eims_other; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  tx_timeout_count; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_EICS ; 
 scalar_t__ e1000_82580 ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igb_tx_timeout(struct net_device *netdev)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;

	/* Do the reset outside of interrupt context */
	adapter->tx_timeout_count++;

	if (hw->mac.type >= e1000_82580)
		hw->dev_spec._82575.global_device_reset = true;

	schedule_work(&adapter->reset_task);
	wr32(E1000_EICS,
	     (adapter->eims_enable_mask & ~adapter->eims_other));
}