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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct ethtool_test {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {void* autoneg; void* forced_speed_duplex; } ;
struct TYPE_4__ {int autoneg_wait_to_complete; int /*<<< orphan*/  autoneg_advertised; } ;
struct TYPE_6__ {TYPE_2__ mac; TYPE_1__ phy; } ;
struct e1000_adapter {int flags; int /*<<< orphan*/  state; TYPE_3__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TEST_FL_FAILED ; 
 int /*<<< orphan*/  ETH_TEST_FL_OFFLINE ; 
 int FLAG_HAS_AMT ; 
 int /*<<< orphan*/  __E1000_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_open (struct net_device*) ; 
 scalar_t__ e1000_eeprom_test (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_intr_test (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_link_test (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_loopback_test (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ e1000_reg_test (struct e1000_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000e_get_hw_control (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_power_up_phy (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_release_hw_control (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_reset (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e_info (char*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void e1000_diag_test(struct net_device *netdev,
			    struct ethtool_test *eth_test, u64 *data)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	u16 autoneg_advertised;
	u8 forced_speed_duplex;
	u8 autoneg;
	bool if_running = netif_running(netdev);

	set_bit(__E1000_TESTING, &adapter->state);

	if (!if_running) {
		/* Get control of and reset hardware */
		if (adapter->flags & FLAG_HAS_AMT)
			e1000e_get_hw_control(adapter);

		e1000e_power_up_phy(adapter);

		adapter->hw.phy.autoneg_wait_to_complete = 1;
		e1000e_reset(adapter);
		adapter->hw.phy.autoneg_wait_to_complete = 0;
	}

	if (eth_test->flags == ETH_TEST_FL_OFFLINE) {
		/* Offline tests */

		/* save speed, duplex, autoneg settings */
		autoneg_advertised = adapter->hw.phy.autoneg_advertised;
		forced_speed_duplex = adapter->hw.mac.forced_speed_duplex;
		autoneg = adapter->hw.mac.autoneg;

		e_info("offline testing starting\n");

		if (if_running)
			/* indicate we're in test mode */
			dev_close(netdev);

		if (e1000_reg_test(adapter, &data[0]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		e1000e_reset(adapter);
		if (e1000_eeprom_test(adapter, &data[1]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		e1000e_reset(adapter);
		if (e1000_intr_test(adapter, &data[2]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		e1000e_reset(adapter);
		if (e1000_loopback_test(adapter, &data[3]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* force this routine to wait until autoneg complete/timeout */
		adapter->hw.phy.autoneg_wait_to_complete = 1;
		e1000e_reset(adapter);
		adapter->hw.phy.autoneg_wait_to_complete = 0;

		if (e1000_link_test(adapter, &data[4]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* restore speed, duplex, autoneg settings */
		adapter->hw.phy.autoneg_advertised = autoneg_advertised;
		adapter->hw.mac.forced_speed_duplex = forced_speed_duplex;
		adapter->hw.mac.autoneg = autoneg;
		e1000e_reset(adapter);

		clear_bit(__E1000_TESTING, &adapter->state);
		if (if_running)
			dev_open(netdev);
	} else {
		/* Online tests */

		e_info("online testing starting\n");

		/* register, eeprom, intr and loopback tests not run online */
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;

		if (e1000_link_test(adapter, &data[4]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		clear_bit(__E1000_TESTING, &adapter->state);
	}

	if (!if_running) {
		e1000e_reset(adapter);

		if (adapter->flags & FLAG_HAS_AMT)
			e1000e_release_hw_control(adapter);
	}

	msleep_interruptible(4 * 1000);
}