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
struct pxamci_host {unsigned long clkrate; scalar_t__ clkrt; scalar_t__ power_mode; int /*<<< orphan*/  cmdat; int /*<<< orphan*/  clk; } ;
struct mmc_ios {int clock; scalar_t__ power_mode; scalar_t__ bus_width; int /*<<< orphan*/  vdd; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ CLKRT_OFF ; 
 int /*<<< orphan*/  CMDAT_INIT ; 
 int /*<<< orphan*/  CMDAT_SD_4DAT ; 
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 scalar_t__ MMC_POWER_ON ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int fls (unsigned int) ; 
 struct pxamci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxamci_set_power (struct pxamci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxamci_stop_clock (struct pxamci_host*) ; 

__attribute__((used)) static void pxamci_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct pxamci_host *host = mmc_priv(mmc);

	if (ios->clock) {
		unsigned long rate = host->clkrate;
		unsigned int clk = rate / ios->clock;

		if (host->clkrt == CLKRT_OFF)
			clk_enable(host->clk);

		if (ios->clock == 26000000) {
			/* to support 26MHz on pxa300/pxa310 */
			host->clkrt = 7;
		} else {
			/* to handle (19.5MHz, 26MHz) */
			if (!clk)
				clk = 1;

			/*
			 * clk might result in a lower divisor than we
			 * desire.  check for that condition and adjust
			 * as appropriate.
			 */
			if (rate / clk > ios->clock)
				clk <<= 1;
			host->clkrt = fls(clk) - 1;
		}

		/*
		 * we write clkrt on the next command
		 */
	} else {
		pxamci_stop_clock(host);
		if (host->clkrt != CLKRT_OFF) {
			host->clkrt = CLKRT_OFF;
			clk_disable(host->clk);
		}
	}

	if (host->power_mode != ios->power_mode) {
		host->power_mode = ios->power_mode;

		pxamci_set_power(host, ios->vdd);

		if (ios->power_mode == MMC_POWER_ON)
			host->cmdat |= CMDAT_INIT;
	}

	if (ios->bus_width == MMC_BUS_WIDTH_4)
		host->cmdat |= CMDAT_SD_4DAT;
	else
		host->cmdat &= ~CMDAT_SD_4DAT;

	pr_debug("PXAMCI: clkrt = %x cmdat = %x\n",
		 host->clkrt, host->cmdat);
}