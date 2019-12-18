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
struct ethtool_pauseparam {scalar_t__ tx_pause; scalar_t__ autoneg; scalar_t__ rx_pause; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int physical_port; scalar_t__ port_type; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 scalar_t__ QLCNIC_GBE ; 
 int /*<<< orphan*/  QLCNIC_NIU_GB_MAC_CONFIG_0 (int) ; 
 int /*<<< orphan*/  QLCNIC_NIU_GB_PAUSE_CTL ; 
 int QLCNIC_NIU_MAX_GBE_PORTS ; 
 int QLCNIC_NIU_MAX_XG_PORTS ; 
 int /*<<< orphan*/  QLCNIC_NIU_XG_PAUSE_CTL ; 
 scalar_t__ QLCNIC_XGBE ; 
 int /*<<< orphan*/  QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCWR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_set_pauseparam (struct qlcnic_adapter*,struct ethtool_pauseparam*) ; 
 int /*<<< orphan*/  qlcnic_gb_rx_flowctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_gb_set_gb0_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_gb_set_gb1_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_gb_set_gb2_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_gb_set_gb3_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_gb_unset_gb0_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_gb_unset_gb1_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_gb_unset_gb2_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_gb_unset_gb3_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_gb_unset_rx_flowctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_xg_set_xg0_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_xg_set_xg1_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_xg_unset_xg0_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_xg_unset_xg1_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlcnic_set_pauseparam(struct net_device *netdev,
			  struct ethtool_pauseparam *pause)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	int port = adapter->ahw->physical_port;
	__u32 val;

	if (qlcnic_83xx_check(adapter))
		return qlcnic_83xx_set_pauseparam(adapter, pause);

	/* read mode */
	if (adapter->ahw->port_type == QLCNIC_GBE) {
		if ((port < 0) || (port > QLCNIC_NIU_MAX_GBE_PORTS))
			return -EIO;
		/* set flow control */
		val = QLCRD32(adapter, QLCNIC_NIU_GB_MAC_CONFIG_0(port));

		if (pause->rx_pause)
			qlcnic_gb_rx_flowctl(val);
		else
			qlcnic_gb_unset_rx_flowctl(val);

		QLCWR32(adapter, QLCNIC_NIU_GB_MAC_CONFIG_0(port),
				val);
		QLCWR32(adapter, QLCNIC_NIU_GB_MAC_CONFIG_0(port), val);
		/* set autoneg */
		val = QLCRD32(adapter, QLCNIC_NIU_GB_PAUSE_CTL);
		switch (port) {
		case 0:
			if (pause->tx_pause)
				qlcnic_gb_unset_gb0_mask(val);
			else
				qlcnic_gb_set_gb0_mask(val);
			break;
		case 1:
			if (pause->tx_pause)
				qlcnic_gb_unset_gb1_mask(val);
			else
				qlcnic_gb_set_gb1_mask(val);
			break;
		case 2:
			if (pause->tx_pause)
				qlcnic_gb_unset_gb2_mask(val);
			else
				qlcnic_gb_set_gb2_mask(val);
			break;
		case 3:
		default:
			if (pause->tx_pause)
				qlcnic_gb_unset_gb3_mask(val);
			else
				qlcnic_gb_set_gb3_mask(val);
			break;
		}
		QLCWR32(adapter, QLCNIC_NIU_GB_PAUSE_CTL, val);
	} else if (adapter->ahw->port_type == QLCNIC_XGBE) {
		if (!pause->rx_pause || pause->autoneg)
			return -EOPNOTSUPP;

		if ((port < 0) || (port > QLCNIC_NIU_MAX_XG_PORTS))
			return -EIO;

		val = QLCRD32(adapter, QLCNIC_NIU_XG_PAUSE_CTL);
		if (port == 0) {
			if (pause->tx_pause)
				qlcnic_xg_unset_xg0_mask(val);
			else
				qlcnic_xg_set_xg0_mask(val);
		} else {
			if (pause->tx_pause)
				qlcnic_xg_unset_xg1_mask(val);
			else
				qlcnic_xg_set_xg1_mask(val);
		}
		QLCWR32(adapter, QLCNIC_NIU_XG_PAUSE_CTL, val);
	} else {
		dev_err(&netdev->dev, "Unknown board type: %x\n",
				adapter->ahw->port_type);
	}
	return 0;
}