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
struct mmc_omap_host {int dma_done; int /*<<< orphan*/  dma_lock; scalar_t__ brs_received; } ;
struct mmc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_omap_xfer_done (struct mmc_omap_host*,struct mmc_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
mmc_omap_dma_done(struct mmc_omap_host *host, struct mmc_data *data)
{
	unsigned long flags;
	int done;

	done = 0;
	spin_lock_irqsave(&host->dma_lock, flags);
	if (host->brs_received)
		done = 1;
	else
		host->dma_done = 1;
	spin_unlock_irqrestore(&host->dma_lock, flags);
	if (done)
		mmc_omap_xfer_done(host, data);
}