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
struct ethtool_ts_info {int so_timestamping; int tx_types; int rx_filters; int /*<<< orphan*/  phc_index; } ;
struct efx_ptp_data {int /*<<< orphan*/  phc_clock; } ;
struct efx_nic {struct efx_ptp_data* ptp_data; } ;

/* Variables and functions */
 int HWTSTAMP_FILTER_NONE ; 
 int HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ ; 
 int HWTSTAMP_FILTER_PTP_V1_L4_EVENT ; 
 int HWTSTAMP_FILTER_PTP_V1_L4_SYNC ; 
 int HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ ; 
 int HWTSTAMP_FILTER_PTP_V2_L4_EVENT ; 
 int HWTSTAMP_FILTER_PTP_V2_L4_SYNC ; 
 int HWTSTAMP_TX_OFF ; 
 int HWTSTAMP_TX_ON ; 
 int SOF_TIMESTAMPING_RAW_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_HARDWARE ; 
 int SOF_TIMESTAMPING_TX_HARDWARE ; 
 int /*<<< orphan*/  ptp_clock_index (int /*<<< orphan*/ ) ; 

void efx_ptp_get_ts_info(struct efx_nic *efx, struct ethtool_ts_info *ts_info)
{
	struct efx_ptp_data *ptp = efx->ptp_data;

	if (!ptp)
		return;

	ts_info->so_timestamping |= (SOF_TIMESTAMPING_TX_HARDWARE |
				     SOF_TIMESTAMPING_RX_HARDWARE |
				     SOF_TIMESTAMPING_RAW_HARDWARE);
	ts_info->phc_index = ptp_clock_index(ptp->phc_clock);
	ts_info->tx_types = 1 << HWTSTAMP_TX_OFF | 1 << HWTSTAMP_TX_ON;
	ts_info->rx_filters = (1 << HWTSTAMP_FILTER_NONE |
			       1 << HWTSTAMP_FILTER_PTP_V1_L4_EVENT |
			       1 << HWTSTAMP_FILTER_PTP_V1_L4_SYNC |
			       1 << HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ |
			       1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT |
			       1 << HWTSTAMP_FILTER_PTP_V2_L4_SYNC |
			       1 << HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ);
}