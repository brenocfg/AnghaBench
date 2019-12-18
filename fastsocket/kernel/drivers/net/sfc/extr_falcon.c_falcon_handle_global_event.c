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
struct falcon_nic_data {int xmac_poll_required; } ;
struct efx_nic {int /*<<< orphan*/  rx_reset; int /*<<< orphan*/  net_dev; struct falcon_nic_data* nic_data; } ;
struct efx_channel {int /*<<< orphan*/  channel; struct efx_nic* efx; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 scalar_t__ EFX_QWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EFX_REV_FALCON_A1 ; 
 scalar_t__ EFX_REV_FALCON_B0 ; 
 scalar_t__ EFX_WORKAROUND_6555 (struct efx_nic*) ; 
 int /*<<< orphan*/  FSF_AA_GLB_EV_RX_RECOVERY ; 
 int /*<<< orphan*/  FSF_AB_GLB_EV_G_PHY0_INTR ; 
 int /*<<< orphan*/  FSF_AB_GLB_EV_XFP_PHY0_INTR ; 
 int /*<<< orphan*/  FSF_AB_GLB_EV_XG_PHY0_INTR ; 
 int /*<<< orphan*/  FSF_BB_GLB_EV_RX_RECOVERY ; 
 int /*<<< orphan*/  FSF_BB_GLB_EV_XG_MGT_INTR ; 
 int /*<<< orphan*/  RESET_TYPE_DISABLE ; 
 int /*<<< orphan*/  RESET_TYPE_RX_RECOVERY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_err ; 

__attribute__((used)) static bool
falcon_handle_global_event(struct efx_channel *channel, efx_qword_t *event)
{
	struct efx_nic *efx = channel->efx;
	struct falcon_nic_data *nic_data = efx->nic_data;

	if (EFX_QWORD_FIELD(*event, FSF_AB_GLB_EV_G_PHY0_INTR) ||
	    EFX_QWORD_FIELD(*event, FSF_AB_GLB_EV_XG_PHY0_INTR) ||
	    EFX_QWORD_FIELD(*event, FSF_AB_GLB_EV_XFP_PHY0_INTR))
		/* Ignored */
		return true;

	if ((efx_nic_rev(efx) == EFX_REV_FALCON_B0) &&
	    EFX_QWORD_FIELD(*event, FSF_BB_GLB_EV_XG_MGT_INTR)) {
		nic_data->xmac_poll_required = true;
		return true;
	}

	if (efx_nic_rev(efx) <= EFX_REV_FALCON_A1 ?
	    EFX_QWORD_FIELD(*event, FSF_AA_GLB_EV_RX_RECOVERY) :
	    EFX_QWORD_FIELD(*event, FSF_BB_GLB_EV_RX_RECOVERY)) {
		netif_err(efx, rx_err, efx->net_dev,
			  "channel %d seen global RX_RESET event. Resetting.\n",
			  channel->channel);

		atomic_inc(&efx->rx_reset);
		efx_schedule_reset(efx, EFX_WORKAROUND_6555(efx) ?
				   RESET_TYPE_RX_RECOVERY : RESET_TYPE_DISABLE);
		return true;
	}

	return false;
}