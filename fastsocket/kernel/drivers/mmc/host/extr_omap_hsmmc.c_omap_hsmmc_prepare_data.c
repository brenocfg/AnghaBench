#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct omap_hsmmc_host {int /*<<< orphan*/  mmc; scalar_t__ use_dma; int /*<<< orphan*/  base; TYPE_2__* data; } ;
struct mmc_request {TYPE_2__* data; TYPE_1__* cmd; } ;
struct TYPE_4__ {int blksz; int blocks; unsigned int timeout_ns; int /*<<< orphan*/  timeout_clks; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK ; 
 int MMC_RSP_BUSY ; 
 int /*<<< orphan*/  OMAP_HSMMC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int omap_hsmmc_start_dma_transfer (struct omap_hsmmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  set_data_timeout (struct omap_hsmmc_host*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
omap_hsmmc_prepare_data(struct omap_hsmmc_host *host, struct mmc_request *req)
{
	int ret;
	host->data = req->data;

	if (req->data == NULL) {
		OMAP_HSMMC_WRITE(host->base, BLK, 0);
		/*
		 * Set an arbitrary 100ms data timeout for commands with
		 * busy signal.
		 */
		if (req->cmd->flags & MMC_RSP_BUSY)
			set_data_timeout(host, 100000000U, 0);
		return 0;
	}

	OMAP_HSMMC_WRITE(host->base, BLK, (req->data->blksz)
					| (req->data->blocks << 16));
	set_data_timeout(host, req->data->timeout_ns, req->data->timeout_clks);

	if (host->use_dma) {
		ret = omap_hsmmc_start_dma_transfer(host, req);
		if (ret != 0) {
			dev_dbg(mmc_dev(host->mmc), "MMC start dma failure\n");
			return ret;
		}
	}
	return 0;
}