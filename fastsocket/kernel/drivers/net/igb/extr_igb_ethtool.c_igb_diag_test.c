#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int autoneg_wait_to_complete; int /*<<< orphan*/  autoneg_advertised; } ;
struct TYPE_5__ {void* autoneg; void* forced_speed_duplex; } ;
struct TYPE_7__ {TYPE_2__ phy; TYPE_1__ mac; } ;
struct igb_adapter {int /*<<< orphan*/  state; TYPE_4__* pdev; TYPE_3__ hw; } ;
struct ethtool_test {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_TEST_FL_FAILED ; 
 int /*<<< orphan*/  ETH_TEST_FL_OFFLINE ; 
 int /*<<< orphan*/  __IGB_TESTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_open (struct net_device*) ; 
 scalar_t__ igb_eeprom_test (struct igb_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ igb_intr_test (struct igb_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ igb_link_test (struct igb_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ igb_loopback_test (struct igb_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igb_power_up_link (struct igb_adapter*) ; 
 scalar_t__ igb_reg_test (struct igb_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igb_reset (struct igb_adapter*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igb_diag_test(struct net_device *netdev,
			  struct ethtool_test *eth_test, u64 *data)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	u16 autoneg_advertised;
	u8 forced_speed_duplex, autoneg;
	bool if_running = netif_running(netdev);

	set_bit(__IGB_TESTING, &adapter->state);
	if (eth_test->flags == ETH_TEST_FL_OFFLINE) {
		/* Offline tests */

		/* save speed, duplex, autoneg settings */
		autoneg_advertised = adapter->hw.phy.autoneg_advertised;
		forced_speed_duplex = adapter->hw.mac.forced_speed_duplex;
		autoneg = adapter->hw.mac.autoneg;

		dev_info(&adapter->pdev->dev, "offline testing starting\n");

		/* power up link for link test */
		igb_power_up_link(adapter);

		/* Link test performed before hardware reset so autoneg doesn't
		 * interfere with test result
		 */
		if (igb_link_test(adapter, &data[4]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		if (if_running)
			/* indicate we're in test mode */
			dev_close(netdev);
		else
			igb_reset(adapter);

		if (igb_reg_test(adapter, &data[0]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		igb_reset(adapter);
		if (igb_eeprom_test(adapter, &data[1]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		igb_reset(adapter);
		if (igb_intr_test(adapter, &data[2]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		igb_reset(adapter);
		/* power up link for loopback test */
		igb_power_up_link(adapter);
		if (igb_loopback_test(adapter, &data[3]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* restore speed, duplex, autoneg settings */
		adapter->hw.phy.autoneg_advertised = autoneg_advertised;
		adapter->hw.mac.forced_speed_duplex = forced_speed_duplex;
		adapter->hw.mac.autoneg = autoneg;

		/* force this routine to wait until autoneg complete/timeout */
		adapter->hw.phy.autoneg_wait_to_complete = true;
		igb_reset(adapter);
		adapter->hw.phy.autoneg_wait_to_complete = false;

		clear_bit(__IGB_TESTING, &adapter->state);
		if (if_running)
			dev_open(netdev);
	} else {
		dev_info(&adapter->pdev->dev, "online testing starting\n");

		/* PHY is powered down when interface is down */
		if (if_running && igb_link_test(adapter, &data[4]))
			eth_test->flags |= ETH_TEST_FL_FAILED;
		else
			data[4] = 0;

		/* Online tests aren't run; pass by default */
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;

		clear_bit(__IGB_TESTING, &adapter->state);
	}
	msleep_interruptible(4 * 1000);
}