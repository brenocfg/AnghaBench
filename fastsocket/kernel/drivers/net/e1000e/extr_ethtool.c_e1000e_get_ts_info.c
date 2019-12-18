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
struct net_device {int dummy; } ;
struct ethtool_ts_info {int so_timestamping; int tx_types; int rx_filters; int /*<<< orphan*/  phc_index; } ;
struct e1000_adapter {int flags; scalar_t__ ptp_clock; } ;

/* Variables and functions */
 int FLAG_HAS_HW_TIMESTAMP ; 
 int HWTSTAMP_FILTER_ALL ; 
 int HWTSTAMP_FILTER_NONE ; 
 int HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ ; 
 int HWTSTAMP_FILTER_PTP_V1_L4_SYNC ; 
 int HWTSTAMP_FILTER_PTP_V2_DELAY_REQ ; 
 int HWTSTAMP_FILTER_PTP_V2_EVENT ; 
 int HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ ; 
 int HWTSTAMP_FILTER_PTP_V2_L2_SYNC ; 
 int HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ ; 
 int HWTSTAMP_FILTER_PTP_V2_L4_SYNC ; 
 int HWTSTAMP_FILTER_PTP_V2_SYNC ; 
 int HWTSTAMP_TX_OFF ; 
 int HWTSTAMP_TX_ON ; 
 int SOF_TIMESTAMPING_RAW_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_HARDWARE ; 
 int SOF_TIMESTAMPING_TX_HARDWARE ; 
 int /*<<< orphan*/  ethtool_op_get_ts_info (struct net_device*,struct ethtool_ts_info*) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ptp_clock_index (scalar_t__) ; 

__attribute__((used)) static int e1000e_get_ts_info(struct net_device *netdev,
			      struct ethtool_ts_info *info)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);

	ethtool_op_get_ts_info(netdev, info);

	if (!(adapter->flags & FLAG_HAS_HW_TIMESTAMP))
		return 0;

	info->so_timestamping |= (SOF_TIMESTAMPING_TX_HARDWARE |
				  SOF_TIMESTAMPING_RX_HARDWARE |
				  SOF_TIMESTAMPING_RAW_HARDWARE);

	info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);

	info->rx_filters = ((1 << HWTSTAMP_FILTER_NONE) |
			    (1 << HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
			    (1 << HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ) |
			    (1 << HWTSTAMP_FILTER_PTP_V2_L4_SYNC) |
			    (1 << HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ) |
			    (1 << HWTSTAMP_FILTER_PTP_V2_L2_SYNC) |
			    (1 << HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ) |
			    (1 << HWTSTAMP_FILTER_PTP_V2_EVENT) |
			    (1 << HWTSTAMP_FILTER_PTP_V2_SYNC) |
			    (1 << HWTSTAMP_FILTER_PTP_V2_DELAY_REQ) |
			    (1 << HWTSTAMP_FILTER_ALL));

	if (adapter->ptp_clock)
		info->phc_index = ptp_clock_index(adapter->ptp_clock);

	return 0;
}