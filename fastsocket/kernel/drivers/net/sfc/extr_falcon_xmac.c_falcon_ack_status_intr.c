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
struct falcon_nic_data {scalar_t__ xmac_poll_required; } ;
struct TYPE_2__ {int /*<<< orphan*/  up; } ;
struct efx_nic {TYPE_1__ link_state; struct falcon_nic_data* nic_data; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 scalar_t__ EFX_REV_FALCON_B0 ; 
 int /*<<< orphan*/  EFX_WORKAROUND_5147 (struct efx_nic*) ; 
 int /*<<< orphan*/  FR_AB_XM_MGT_INT_MSK ; 
 scalar_t__ LOOPBACK_INTERNAL (struct efx_nic*) ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void falcon_ack_status_intr(struct efx_nic *efx)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	efx_oword_t reg;

	if ((efx_nic_rev(efx) != EFX_REV_FALCON_B0) || LOOPBACK_INTERNAL(efx))
		return;

	/* We expect xgmii faults if the wireside link is down */
	if (!EFX_WORKAROUND_5147(efx) || !efx->link_state.up)
		return;

	/* We can only use this interrupt to signal the negative edge of
	 * xaui_align [we have to poll the positive edge]. */
	if (nic_data->xmac_poll_required)
		return;

	efx_reado(efx, &reg, FR_AB_XM_MGT_INT_MSK);
}