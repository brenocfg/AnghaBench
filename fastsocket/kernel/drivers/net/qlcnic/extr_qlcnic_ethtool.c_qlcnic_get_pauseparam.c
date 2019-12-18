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
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct ethtool_pauseparam {int rx_pause; int tx_pause; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int physical_port; scalar_t__ port_type; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_GBE ; 
 int /*<<< orphan*/  QLCNIC_NIU_GB_MAC_CONFIG_0 (int) ; 
 int /*<<< orphan*/  QLCNIC_NIU_GB_PAUSE_CTL ; 
 int QLCNIC_NIU_MAX_GBE_PORTS ; 
 int QLCNIC_NIU_MAX_XG_PORTS ; 
 int /*<<< orphan*/  QLCNIC_NIU_XG_PAUSE_CTL ; 
 scalar_t__ QLCNIC_XGBE ; 
 int /*<<< orphan*/  QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_get_pauseparam (struct qlcnic_adapter*,struct ethtool_pauseparam*) ; 
 int /*<<< orphan*/  qlcnic_gb_get_gb0_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_gb_get_gb1_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_gb_get_gb2_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_gb_get_gb3_mask (int /*<<< orphan*/ ) ; 
 int qlcnic_gb_get_rx_flowctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_xg_get_xg0_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_xg_get_xg1_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qlcnic_get_pauseparam(struct net_device *netdev,
			  struct ethtool_pauseparam *pause)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	int port = adapter->ahw->physical_port;
	__u32 val;

	if (qlcnic_83xx_check(adapter)) {
		qlcnic_83xx_get_pauseparam(adapter, pause);
		return;
	}
	if (adapter->ahw->port_type == QLCNIC_GBE) {
		if ((port < 0) || (port > QLCNIC_NIU_MAX_GBE_PORTS))
			return;
		/* get flow control settings */
		val = QLCRD32(adapter, QLCNIC_NIU_GB_MAC_CONFIG_0(port));
		pause->rx_pause = qlcnic_gb_get_rx_flowctl(val);
		val = QLCRD32(adapter, QLCNIC_NIU_GB_PAUSE_CTL);
		switch (port) {
		case 0:
			pause->tx_pause = !(qlcnic_gb_get_gb0_mask(val));
			break;
		case 1:
			pause->tx_pause = !(qlcnic_gb_get_gb1_mask(val));
			break;
		case 2:
			pause->tx_pause = !(qlcnic_gb_get_gb2_mask(val));
			break;
		case 3:
		default:
			pause->tx_pause = !(qlcnic_gb_get_gb3_mask(val));
			break;
		}
	} else if (adapter->ahw->port_type == QLCNIC_XGBE) {
		if ((port < 0) || (port > QLCNIC_NIU_MAX_XG_PORTS))
			return;
		pause->rx_pause = 1;
		val = QLCRD32(adapter, QLCNIC_NIU_XG_PAUSE_CTL);
		if (port == 0)
			pause->tx_pause = !(qlcnic_xg_get_xg0_mask(val));
		else
			pause->tx_pause = !(qlcnic_xg_get_xg1_mask(val));
	} else {
		dev_err(&netdev->dev, "Unknown board type: %x\n",
					adapter->ahw->port_type);
	}
}