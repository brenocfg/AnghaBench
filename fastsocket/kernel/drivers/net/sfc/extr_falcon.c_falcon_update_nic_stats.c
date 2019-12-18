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
struct falcon_nic_data {int stats_pending; scalar_t__* stats_dma_done; scalar_t__ stats_disable_count; } ;
struct efx_nic {int /*<<< orphan*/  n_rx_nodesc_drop_cnt; struct falcon_nic_data* nic_data; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 scalar_t__ EFX_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALCON_STATS_DONE ; 
 int /*<<< orphan*/  FRF_AB_RX_NODESC_DROP_CNT ; 
 int /*<<< orphan*/  FR_AZ_RX_NODESC_DROP ; 
 int /*<<< orphan*/  efx_reado (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  falcon_update_stats_xmac (struct efx_nic*) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static void falcon_update_nic_stats(struct efx_nic *efx)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	efx_oword_t cnt;

	if (nic_data->stats_disable_count)
		return;

	efx_reado(efx, &cnt, FR_AZ_RX_NODESC_DROP);
	efx->n_rx_nodesc_drop_cnt +=
		EFX_OWORD_FIELD(cnt, FRF_AB_RX_NODESC_DROP_CNT);

	if (nic_data->stats_pending &&
	    *nic_data->stats_dma_done == FALCON_STATS_DONE) {
		nic_data->stats_pending = false;
		rmb(); /* read the done flag before the stats */
		falcon_update_stats_xmac(efx);
	}
}