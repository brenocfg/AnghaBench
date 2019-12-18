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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct ethtool_test {int /*<<< orphan*/  flags; } ;
struct e1000_hw {void* autoneg; void* forced_speed_duplex; int /*<<< orphan*/  autoneg_advertised; } ;
struct e1000_adapter {int /*<<< orphan*/  flags; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TEST_FL_FAILED ; 
 int /*<<< orphan*/  ETH_TEST_FL_OFFLINE ; 
 int /*<<< orphan*/  __E1000_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_open (struct net_device*) ; 
 scalar_t__ e1000_eeprom_test (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_intr_test (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_link_test (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_loopback_test (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_power_up_phy (struct e1000_adapter*) ; 
 scalar_t__ e1000_reg_test (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_reset (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e_info (struct e1000_hw*,char*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void e1000_diag_test(struct net_device *netdev,
			    struct ethtool_test *eth_test, u64 *data)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	bool if_running = netif_running(netdev);

	set_bit(__E1000_TESTING, &adapter->flags);
	if (eth_test->flags == ETH_TEST_FL_OFFLINE) {
		/* Offline tests */

		/* save speed, duplex, autoneg settings */
		u16 autoneg_advertised = hw->autoneg_advertised;
		u8 forced_speed_duplex = hw->forced_speed_duplex;
		u8 autoneg = hw->autoneg;

		e_info(hw, "offline testing starting\n");

		/* Link test performed before hardware reset so autoneg doesn't
		 * interfere with test result */
		if (e1000_link_test(adapter, &data[4]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		if (if_running)
			/* indicate we're in test mode */
			dev_close(netdev);
		else
			e1000_reset(adapter);

		if (e1000_reg_test(adapter, &data[0]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		e1000_reset(adapter);
		if (e1000_eeprom_test(adapter, &data[1]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		e1000_reset(adapter);
		if (e1000_intr_test(adapter, &data[2]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		e1000_reset(adapter);
		/* make sure the phy is powered up */
		e1000_power_up_phy(adapter);
		if (e1000_loopback_test(adapter, &data[3]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* restore speed, duplex, autoneg settings */
		hw->autoneg_advertised = autoneg_advertised;
		hw->forced_speed_duplex = forced_speed_duplex;
		hw->autoneg = autoneg;

		e1000_reset(adapter);
		clear_bit(__E1000_TESTING, &adapter->flags);
		if (if_running)
			dev_open(netdev);
	} else {
		e_info(hw, "online testing starting\n");
		/* Online tests */
		if (e1000_link_test(adapter, &data[4]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* Online tests aren't run; pass by default */
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;

		clear_bit(__E1000_TESTING, &adapter->flags);
	}
	msleep_interruptible(4 * 1000);
}