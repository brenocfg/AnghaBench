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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/ * addr; } ;
struct efx_nic {TYPE_1__ stats_buffer; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 size_t MC_CMD_MAC_GENERATION_END ; 
 int MC_CMD_MAC_NSTATS ; 
 int /*<<< orphan*/  STATS_GENERATION_INVALID ; 
 int /*<<< orphan*/  efx_mcdi_mac_stats (struct efx_nic*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void siena_start_nic_stats(struct efx_nic *efx)
{
	__le64 *dma_stats = efx->stats_buffer.addr;

	dma_stats[MC_CMD_MAC_GENERATION_END] = STATS_GENERATION_INVALID;

	efx_mcdi_mac_stats(efx, efx->stats_buffer.dma_addr,
			   MC_CMD_MAC_NSTATS * sizeof(u64), 1, 0);
}