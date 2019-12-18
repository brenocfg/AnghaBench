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
struct net_device {int dummy; } ;
struct TYPE_2__ {int get_link_status; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct igbvf_adapter {int /*<<< orphan*/  eims_other; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  state; int /*<<< orphan*/  int_counter1; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIMS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  __IGBVF_DOWN ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t igbvf_msix_other(int irq, void *data)
{
	struct net_device *netdev = data;
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;

	adapter->int_counter1++;

	netif_carrier_off(netdev);
	hw->mac.get_link_status = 1;
	if (!test_bit(__IGBVF_DOWN, &adapter->state))
		mod_timer(&adapter->watchdog_timer, jiffies + 1);

	ew32(EIMS, adapter->eims_other);

	return IRQ_HANDLED;
}