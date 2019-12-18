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
struct mmc_request {int /*<<< orphan*/  cmd; } ;
struct mmc_omap_host {int /*<<< orphan*/  dma_ch; scalar_t__ dma_in_use; struct mmc_request* mrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  mmc_omap_prepare_data (struct mmc_omap_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_omap_start_command (struct mmc_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_start_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmc_omap_start_request(struct mmc_omap_host *host,
				   struct mmc_request *req)
{
	BUG_ON(host->mrq != NULL);

	host->mrq = req;

	/* only touch fifo AFTER the controller readies it */
	mmc_omap_prepare_data(host, req);
	mmc_omap_start_command(host, req->cmd);
	if (host->dma_in_use)
		omap_start_dma(host->dma_ch);
	BUG_ON(irqs_disabled());
}