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
struct falcon_nic_data {int stats_pending; scalar_t__* stats_dma_done; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; struct falcon_nic_data* nic_data; } ;

/* Variables and functions */
 scalar_t__ FALCON_STATS_DONE ; 
 int /*<<< orphan*/  falcon_update_stats_xmac (struct efx_nic*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static void falcon_stats_complete(struct efx_nic *efx)
{
	struct falcon_nic_data *nic_data = efx->nic_data;

	if (!nic_data->stats_pending)
		return;

	nic_data->stats_pending = false;
	if (*nic_data->stats_dma_done == FALCON_STATS_DONE) {
		rmb(); /* read the done flag before the stats */
		falcon_update_stats_xmac(efx);
	} else {
		netif_err(efx, hw, efx->net_dev,
			  "timed out waiting for statistics\n");
	}
}