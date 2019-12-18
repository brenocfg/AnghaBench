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
typedef  int u32 ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
struct efx_channel {struct efx_nic* efx; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMDDONE_DATALEN ; 
 int /*<<< orphan*/  CMDDONE_ERRNO ; 
 int /*<<< orphan*/  CMDDONE_SEQ ; 
 int EFX_QWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  FLR_VF ; 
 int /*<<< orphan*/  MCDI_EVENT_CODE ; 
#define  MCDI_EVENT_CODE_BADSSERT 139 
#define  MCDI_EVENT_CODE_CMDDONE 138 
#define  MCDI_EVENT_CODE_FLR 137 
#define  MCDI_EVENT_CODE_LINKCHANGE 136 
#define  MCDI_EVENT_CODE_MAC_STATS_DMA 135 
#define  MCDI_EVENT_CODE_PMNOTICE 134 
#define  MCDI_EVENT_CODE_PTP_FAULT 133 
#define  MCDI_EVENT_CODE_PTP_PPS 132 
#define  MCDI_EVENT_CODE_PTP_RX 131 
#define  MCDI_EVENT_CODE_REBOOT 130 
#define  MCDI_EVENT_CODE_SCHEDERR 129 
#define  MCDI_EVENT_CODE_SENSOREVT 128 
 int /*<<< orphan*/  MCDI_EVENT_DATA ; 
 int /*<<< orphan*/  MCDI_EVENT_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_mcdi_ev_cpl (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_mcdi_ev_death (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_mcdi_process_link_change (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_mcdi_sensor_event (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_ptp_event (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_sriov_flr (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_info (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wol ; 

void efx_mcdi_process_event(struct efx_channel *channel,
			    efx_qword_t *event)
{
	struct efx_nic *efx = channel->efx;
	int code = EFX_QWORD_FIELD(*event, MCDI_EVENT_CODE);
	u32 data = EFX_QWORD_FIELD(*event, MCDI_EVENT_DATA);

	switch (code) {
	case MCDI_EVENT_CODE_BADSSERT:
		netif_err(efx, hw, efx->net_dev,
			  "MC watchdog or assertion failure at 0x%x\n", data);
		efx_mcdi_ev_death(efx, EINTR);
		break;

	case MCDI_EVENT_CODE_PMNOTICE:
		netif_info(efx, wol, efx->net_dev, "MCDI PM event.\n");
		break;

	case MCDI_EVENT_CODE_CMDDONE:
		efx_mcdi_ev_cpl(efx,
				MCDI_EVENT_FIELD(*event, CMDDONE_SEQ),
				MCDI_EVENT_FIELD(*event, CMDDONE_DATALEN),
				MCDI_EVENT_FIELD(*event, CMDDONE_ERRNO));
		break;

	case MCDI_EVENT_CODE_LINKCHANGE:
		efx_mcdi_process_link_change(efx, event);
		break;
	case MCDI_EVENT_CODE_SENSOREVT:
		efx_mcdi_sensor_event(efx, event);
		break;
	case MCDI_EVENT_CODE_SCHEDERR:
		netif_info(efx, hw, efx->net_dev,
			   "MC Scheduler error address=0x%x\n", data);
		break;
	case MCDI_EVENT_CODE_REBOOT:
		netif_info(efx, hw, efx->net_dev, "MC Reboot\n");
		efx_mcdi_ev_death(efx, EIO);
		break;
	case MCDI_EVENT_CODE_MAC_STATS_DMA:
		/* MAC stats are gather lazily.  We can ignore this. */
		break;
	case MCDI_EVENT_CODE_FLR:
		efx_sriov_flr(efx, MCDI_EVENT_FIELD(*event, FLR_VF));
		break;
	case MCDI_EVENT_CODE_PTP_RX:
	case MCDI_EVENT_CODE_PTP_FAULT:
	case MCDI_EVENT_CODE_PTP_PPS:
		efx_ptp_event(efx, event);
		break;

	default:
		netif_err(efx, hw, efx->net_dev, "Unknown MCDI event 0x%x\n",
			  code);
	}
}