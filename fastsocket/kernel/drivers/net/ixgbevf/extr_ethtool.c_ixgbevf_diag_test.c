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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  hw; } ;
struct ethtool_test {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TEST_FL_FAILED ; 
 int /*<<< orphan*/  ETH_TEST_FL_OFFLINE ; 
 int /*<<< orphan*/  __IXGBEVF_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_open (struct net_device*) ; 
 int /*<<< orphan*/  hw_dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ixgbevf_link_test (struct ixgbevf_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ ixgbevf_reg_test (struct ixgbevf_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbevf_reset (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbevf_diag_test(struct net_device *netdev,
			      struct ethtool_test *eth_test, u64 *data)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);
	bool if_running = netif_running(netdev);

	set_bit(__IXGBEVF_TESTING, &adapter->state);
	if (eth_test->flags == ETH_TEST_FL_OFFLINE) {
		/* Offline tests */

		hw_dbg(&adapter->hw, "offline testing starting\n");

		/* Link test performed before hardware reset so autoneg doesn't
		 * interfere with test result */
		if (ixgbevf_link_test(adapter, &data[1]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		if (if_running)
			/* indicate we're in test mode */
			dev_close(netdev);
		else
			ixgbevf_reset(adapter);

		hw_dbg(&adapter->hw, "register testing starting\n");
		if (ixgbevf_reg_test(adapter, &data[0]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		ixgbevf_reset(adapter);

		clear_bit(__IXGBEVF_TESTING, &adapter->state);
		if (if_running)
			dev_open(netdev);
	} else {
		hw_dbg(&adapter->hw, "online testing starting\n");
		/* Online tests */
		if (ixgbevf_link_test(adapter, &data[1]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* Online tests aren't run; pass by default */
		data[0] = 0;

		clear_bit(__IXGBEVF_TESTING, &adapter->state);
	}
	msleep_interruptible(4 * 1000);
}