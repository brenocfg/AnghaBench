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
struct hwtstamp_config {scalar_t__ tx_type; int rx_filter; scalar_t__ flags; } ;
struct efx_nic {TYPE_1__* ptp_data; } ;
struct TYPE_2__ {unsigned int mode; struct hwtstamp_config config; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
#define  HWTSTAMP_FILTER_NONE 140 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 139 
#define  HWTSTAMP_FILTER_PTP_V1_L4_EVENT 138 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 137 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 136 
#define  HWTSTAMP_FILTER_PTP_V2_EVENT 135 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 134 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 133 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 132 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 131 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 130 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 129 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 128 
 scalar_t__ HWTSTAMP_TX_OFF ; 
 scalar_t__ HWTSTAMP_TX_ON ; 
 unsigned int MC_CMD_PTP_MODE_V1 ; 
 unsigned int MC_CMD_PTP_MODE_V2 ; 
 unsigned int MC_CMD_PTP_MODE_V2_ENHANCED ; 
 int efx_ptp_change_mode (struct efx_nic*,int,unsigned int) ; 

__attribute__((used)) static int efx_ptp_ts_init(struct efx_nic *efx, struct hwtstamp_config *init)
{
	bool enable_wanted = false;
	unsigned int new_mode;
	int rc;

	if (init->flags)
		return -EINVAL;

	if ((init->tx_type != HWTSTAMP_TX_OFF) &&
	    (init->tx_type != HWTSTAMP_TX_ON))
		return -ERANGE;

	new_mode = efx->ptp_data->mode;
	/* Determine whether any PTP HW operations are required */
	switch (init->rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		init->rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		new_mode = MC_CMD_PTP_MODE_V1;
		enable_wanted = true;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	/* Although these three are accepted only IPV4 packets will be
	 * timestamped
	 */
		init->rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
		new_mode = MC_CMD_PTP_MODE_V2_ENHANCED;
		enable_wanted = true;
		break;
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		/* Non-IP + IPv6 timestamping not supported */
		return -ERANGE;
		break;
	default:
		return -ERANGE;
	}

	if (init->tx_type != HWTSTAMP_TX_OFF)
		enable_wanted = true;

	/* Old versions of the firmware do not support the improved
	 * UUID filtering option (SF bug 33070).  If the firmware does
	 * not accept the enhanced mode, fall back to the standard PTP
	 * v2 UUID filtering.
	 */
	rc = efx_ptp_change_mode(efx, enable_wanted, new_mode);
	if ((rc != 0) && (new_mode == MC_CMD_PTP_MODE_V2_ENHANCED))
		rc = efx_ptp_change_mode(efx, enable_wanted, MC_CMD_PTP_MODE_V2);
	if (rc != 0)
		return rc;

	efx->ptp_data->config = *init;

	return 0;
}