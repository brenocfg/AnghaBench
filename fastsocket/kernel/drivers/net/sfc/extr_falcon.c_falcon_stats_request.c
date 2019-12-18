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
struct falcon_nic_data {int stats_pending; int stats_disable_count; int /*<<< orphan*/  stats_timer; int /*<<< orphan*/ * stats_dma_done; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_addr; } ;
struct efx_nic {TYPE_1__ stats_buffer; struct falcon_nic_data* nic_data; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_POPULATE_OWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALCON_STATS_NOT_DONE ; 
 int /*<<< orphan*/  FRF_AB_MAC_STAT_DMA_ADR ; 
 int /*<<< orphan*/  FRF_AB_MAC_STAT_DMA_CMD ; 
 int /*<<< orphan*/  FR_AB_MAC_STAT_DMA ; 
 int HZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  efx_writeo (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_up (scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void falcon_stats_request(struct efx_nic *efx)
{
	struct falcon_nic_data *nic_data = efx->nic_data;
	efx_oword_t reg;

	WARN_ON(nic_data->stats_pending);
	WARN_ON(nic_data->stats_disable_count);

	if (nic_data->stats_dma_done == NULL)
		return;	/* no mac selected */

	*nic_data->stats_dma_done = FALCON_STATS_NOT_DONE;
	nic_data->stats_pending = true;
	wmb(); /* ensure done flag is clear */

	/* Initiate DMA transfer of stats */
	EFX_POPULATE_OWORD_2(reg,
			     FRF_AB_MAC_STAT_DMA_CMD, 1,
			     FRF_AB_MAC_STAT_DMA_ADR,
			     efx->stats_buffer.dma_addr);
	efx_writeo(efx, &reg, FR_AB_MAC_STAT_DMA);

	mod_timer(&nic_data->stats_timer, round_jiffies_up(jiffies + HZ / 2));
}