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
struct omap_hsmmc_host {int dma_line_tx; int dma_line_rx; } ;
struct mmc_data {int flags; } ;

/* Variables and functions */
 int MMC_DATA_WRITE ; 

__attribute__((used)) static int omap_hsmmc_get_dma_sync_dev(struct omap_hsmmc_host *host,
				     struct mmc_data *data)
{
	int sync_dev;

	if (data->flags & MMC_DATA_WRITE)
		sync_dev = host->dma_line_tx;
	else
		sync_dev = host->dma_line_rx;
	return sync_dev;
}