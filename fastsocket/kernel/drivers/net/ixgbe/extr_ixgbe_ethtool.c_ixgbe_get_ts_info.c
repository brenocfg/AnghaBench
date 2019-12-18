#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {int type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct ixgbe_adapter {int /*<<< orphan*/  ptp_clock; TYPE_2__ hw; } ;
struct ethtool_ts_info {int so_timestamping; int phc_index; int tx_types; int rx_filters; } ;

/* Variables and functions */
 int HWTSTAMP_FILTER_NONE ; 
 int HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ ; 
 int HWTSTAMP_FILTER_PTP_V1_L4_SYNC ; 
 int HWTSTAMP_FILTER_PTP_V2_DELAY_REQ ; 
 int HWTSTAMP_FILTER_PTP_V2_EVENT ; 
 int HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ ; 
 int HWTSTAMP_FILTER_PTP_V2_L2_EVENT ; 
 int HWTSTAMP_FILTER_PTP_V2_L2_SYNC ; 
 int HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ ; 
 int HWTSTAMP_FILTER_PTP_V2_L4_EVENT ; 
 int HWTSTAMP_FILTER_PTP_V2_L4_SYNC ; 
 int HWTSTAMP_FILTER_PTP_V2_SYNC ; 
 int HWTSTAMP_TX_OFF ; 
 int HWTSTAMP_TX_ON ; 
 int SOF_TIMESTAMPING_RAW_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_SOFTWARE ; 
 int SOF_TIMESTAMPING_SOFTWARE ; 
 int SOF_TIMESTAMPING_TX_HARDWARE ; 
 int SOF_TIMESTAMPING_TX_SOFTWARE ; 
 int ethtool_op_get_ts_info (struct net_device*,struct ethtool_ts_info*) ; 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int ptp_clock_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbe_get_ts_info(struct net_device *dev,
			     struct ethtool_ts_info *info)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);

	switch (adapter->hw.mac.type) {
#ifdef CONFIG_IXGBE_PTP
	case ixgbe_mac_X540:
	case ixgbe_mac_82599EB:
		info->so_timestamping =
			SOF_TIMESTAMPING_TX_SOFTWARE |
			SOF_TIMESTAMPING_RX_SOFTWARE |
			SOF_TIMESTAMPING_SOFTWARE |
			SOF_TIMESTAMPING_TX_HARDWARE |
			SOF_TIMESTAMPING_RX_HARDWARE |
			SOF_TIMESTAMPING_RAW_HARDWARE;

		if (adapter->ptp_clock)
			info->phc_index = ptp_clock_index(adapter->ptp_clock);
		else
			info->phc_index = -1;

		info->tx_types =
			(1 << HWTSTAMP_TX_OFF) |
			(1 << HWTSTAMP_TX_ON);

		info->rx_filters =
			(1 << HWTSTAMP_FILTER_NONE) |
			(1 << HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
			(1 << HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ) |
			(1 << HWTSTAMP_FILTER_PTP_V2_L2_EVENT) |
			(1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
			(1 << HWTSTAMP_FILTER_PTP_V2_SYNC) |
			(1 << HWTSTAMP_FILTER_PTP_V2_L2_SYNC) |
			(1 << HWTSTAMP_FILTER_PTP_V2_L4_SYNC) |
			(1 << HWTSTAMP_FILTER_PTP_V2_DELAY_REQ) |
			(1 << HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ) |
			(1 << HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ) |
			(1 << HWTSTAMP_FILTER_PTP_V2_EVENT);
		break;
#endif /* CONFIG_IXGBE_PTP */
	default:
		return ethtool_op_get_ts_info(dev, info);
		break;
	}
	return 0;
}