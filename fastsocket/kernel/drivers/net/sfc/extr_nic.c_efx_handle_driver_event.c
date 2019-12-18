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
struct efx_nic {int /*<<< orphan*/  net_dev; int /*<<< orphan*/  rx_reset; } ;
struct efx_channel {int /*<<< orphan*/  channel; struct efx_nic* efx; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 unsigned int EFX_QWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int EFX_VI_BASE ; 
 int /*<<< orphan*/  EFX_WORKAROUND_6555 (struct efx_nic*) ; 
#define  FSE_AA_RX_RECOVER_EV 136 
#define  FSE_AZ_EVQ_INIT_DONE_EV 135 
#define  FSE_AZ_RX_DESCQ_FLS_DONE_EV 134 
#define  FSE_AZ_SRM_UPD_DONE_EV 133 
#define  FSE_AZ_TIMER_EV 132 
#define  FSE_AZ_TX_DESCQ_FLS_DONE_EV 131 
#define  FSE_AZ_WAKE_UP_EV 130 
#define  FSE_BZ_RX_DSC_ERROR_EV 129 
#define  FSE_BZ_TX_DSC_ERROR_EV 128 
 int /*<<< orphan*/  FSF_AZ_DRIVER_EV_SUBCODE ; 
 int /*<<< orphan*/  FSF_AZ_DRIVER_EV_SUBDATA ; 
 int /*<<< orphan*/  RESET_TYPE_DISABLE ; 
 int /*<<< orphan*/  RESET_TYPE_RX_DESC_FETCH ; 
 int /*<<< orphan*/  RESET_TYPE_RX_RECOVERY ; 
 int /*<<< orphan*/  RESET_TYPE_TX_DESC_FETCH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_handle_rx_flush_done (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_handle_tx_flush_done (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_sriov_desc_fetch_err (struct efx_nic*,unsigned int) ; 
 int /*<<< orphan*/  efx_sriov_rx_flush_done (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_sriov_tx_flush_done (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  netif_vdbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static void
efx_handle_driver_event(struct efx_channel *channel, efx_qword_t *event)
{
	struct efx_nic *efx = channel->efx;
	unsigned int ev_sub_code;
	unsigned int ev_sub_data;

	ev_sub_code = EFX_QWORD_FIELD(*event, FSF_AZ_DRIVER_EV_SUBCODE);
	ev_sub_data = EFX_QWORD_FIELD(*event, FSF_AZ_DRIVER_EV_SUBDATA);

	switch (ev_sub_code) {
	case FSE_AZ_TX_DESCQ_FLS_DONE_EV:
		netif_vdbg(efx, hw, efx->net_dev, "channel %d TXQ %d flushed\n",
			   channel->channel, ev_sub_data);
		efx_handle_tx_flush_done(efx, event);
		efx_sriov_tx_flush_done(efx, event);
		break;
	case FSE_AZ_RX_DESCQ_FLS_DONE_EV:
		netif_vdbg(efx, hw, efx->net_dev, "channel %d RXQ %d flushed\n",
			   channel->channel, ev_sub_data);
		efx_handle_rx_flush_done(efx, event);
		efx_sriov_rx_flush_done(efx, event);
		break;
	case FSE_AZ_EVQ_INIT_DONE_EV:
		netif_dbg(efx, hw, efx->net_dev,
			  "channel %d EVQ %d initialised\n",
			  channel->channel, ev_sub_data);
		break;
	case FSE_AZ_SRM_UPD_DONE_EV:
		netif_vdbg(efx, hw, efx->net_dev,
			   "channel %d SRAM update done\n", channel->channel);
		break;
	case FSE_AZ_WAKE_UP_EV:
		netif_vdbg(efx, hw, efx->net_dev,
			   "channel %d RXQ %d wakeup event\n",
			   channel->channel, ev_sub_data);
		break;
	case FSE_AZ_TIMER_EV:
		netif_vdbg(efx, hw, efx->net_dev,
			   "channel %d RX queue %d timer expired\n",
			   channel->channel, ev_sub_data);
		break;
	case FSE_AA_RX_RECOVER_EV:
		netif_err(efx, rx_err, efx->net_dev,
			  "channel %d seen DRIVER RX_RESET event. "
			"Resetting.\n", channel->channel);
		atomic_inc(&efx->rx_reset);
		efx_schedule_reset(efx,
				   EFX_WORKAROUND_6555(efx) ?
				   RESET_TYPE_RX_RECOVERY :
				   RESET_TYPE_DISABLE);
		break;
	case FSE_BZ_RX_DSC_ERROR_EV:
		if (ev_sub_data < EFX_VI_BASE) {
			netif_err(efx, rx_err, efx->net_dev,
				  "RX DMA Q %d reports descriptor fetch error."
				  " RX Q %d is disabled.\n", ev_sub_data,
				  ev_sub_data);
			efx_schedule_reset(efx, RESET_TYPE_RX_DESC_FETCH);
		} else
			efx_sriov_desc_fetch_err(efx, ev_sub_data);
		break;
	case FSE_BZ_TX_DSC_ERROR_EV:
		if (ev_sub_data < EFX_VI_BASE) {
			netif_err(efx, tx_err, efx->net_dev,
				  "TX DMA Q %d reports descriptor fetch error."
				  " TX Q %d is disabled.\n", ev_sub_data,
				  ev_sub_data);
			efx_schedule_reset(efx, RESET_TYPE_TX_DESC_FETCH);
		} else
			efx_sriov_desc_fetch_err(efx, ev_sub_data);
		break;
	default:
		netif_vdbg(efx, hw, efx->net_dev,
			   "channel %d unknown driver event code %d "
			   "data %04x\n", channel->channel, ev_sub_code,
			   ev_sub_data);
		break;
	}
}