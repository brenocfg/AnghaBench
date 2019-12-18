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
struct omap_hsmmc_host {scalar_t__ power_mode; int /*<<< orphan*/  mmc; int /*<<< orphan*/  dpm_state; int /*<<< orphan*/  fclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLED ; 
 scalar_t__ MMC_POWER_OFF ; 
 int /*<<< orphan*/  OMAP_MMC_SLEEP_TIMEOUT ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hsmmc_context_save (struct omap_hsmmc_host*) ; 

__attribute__((used)) static int omap_hsmmc_enabled_to_disabled(struct omap_hsmmc_host *host)
{
	omap_hsmmc_context_save(host);
	clk_disable(host->fclk);
	host->dpm_state = DISABLED;

	dev_dbg(mmc_dev(host->mmc), "ENABLED -> DISABLED\n");

	if (host->power_mode == MMC_POWER_OFF)
		return 0;

	return msecs_to_jiffies(OMAP_MMC_SLEEP_TIMEOUT);
}