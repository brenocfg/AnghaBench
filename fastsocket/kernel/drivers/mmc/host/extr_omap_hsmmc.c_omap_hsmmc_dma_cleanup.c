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
struct omap_hsmmc_host {int dma_ch; TYPE_1__* data; int /*<<< orphan*/  sem; int /*<<< orphan*/  dma_len; int /*<<< orphan*/  mmc; scalar_t__ use_dma; } ;
struct TYPE_2__ {int error; int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_free_dma (int) ; 
 int /*<<< orphan*/  omap_hsmmc_get_dma_dir (struct omap_hsmmc_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap_hsmmc_dma_cleanup(struct omap_hsmmc_host *host, int errno)
{
	host->data->error = errno;

	if (host->use_dma && host->dma_ch != -1) {
		dma_unmap_sg(mmc_dev(host->mmc), host->data->sg, host->dma_len,
			omap_hsmmc_get_dma_dir(host, host->data));
		omap_free_dma(host->dma_ch);
		host->dma_ch = -1;
		up(&host->sem);
	}
	host->data = NULL;
}