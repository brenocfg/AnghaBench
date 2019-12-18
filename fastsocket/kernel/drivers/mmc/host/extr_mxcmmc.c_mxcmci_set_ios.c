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
struct mxcmci_host {scalar_t__ power_mode; int /*<<< orphan*/  clock; scalar_t__ base; int /*<<< orphan*/  cmdat; TYPE_1__* pdata; int /*<<< orphan*/  dma; } ;
struct mmc_ios {scalar_t__ bus_width; scalar_t__ power_mode; int /*<<< orphan*/  clock; int /*<<< orphan*/  vdd; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* setpower ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_DAT_CONT_BUS_WIDTH_4 ; 
 int /*<<< orphan*/  CMD_DAT_CONT_INIT ; 
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 scalar_t__ MMC_POWER_ON ; 
 scalar_t__ MMC_REG_STR_STP_CLK ; 
 int /*<<< orphan*/  STR_STP_CLK_START_CLK ; 
 int /*<<< orphan*/  STR_STP_CLK_STOP_CLK ; 
 int /*<<< orphan*/  imx_dma_config_burstlen (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 struct mxcmci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mxcmci_set_clk_rate (struct mxcmci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mxcmci_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct mxcmci_host *host = mmc_priv(mmc);
#ifdef HAS_DMA
	unsigned int blen;
	/*
	 * use burstlen of 64 in 4 bit mode (--> reg value  0)
	 * use burstlen of 16 in 1 bit mode (--> reg value 16)
	 */
	if (ios->bus_width == MMC_BUS_WIDTH_4)
		blen = 0;
	else
		blen = 16;

	imx_dma_config_burstlen(host->dma, blen);
#endif
	if (ios->bus_width == MMC_BUS_WIDTH_4)
		host->cmdat |= CMD_DAT_CONT_BUS_WIDTH_4;
	else
		host->cmdat &= ~CMD_DAT_CONT_BUS_WIDTH_4;

	if (host->power_mode != ios->power_mode) {
		if (host->pdata && host->pdata->setpower)
			host->pdata->setpower(mmc_dev(mmc), ios->vdd);
		host->power_mode = ios->power_mode;
		if (ios->power_mode == MMC_POWER_ON)
			host->cmdat |= CMD_DAT_CONT_INIT;
	}

	if (ios->clock) {
		mxcmci_set_clk_rate(host, ios->clock);
		writew(STR_STP_CLK_START_CLK, host->base + MMC_REG_STR_STP_CLK);
	} else {
		writew(STR_STP_CLK_STOP_CLK, host->base + MMC_REG_STR_STP_CLK);
	}

	host->clock = ios->clock;
}