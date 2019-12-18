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
struct omap_hsmmc_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  dpm_state; int /*<<< orphan*/  fclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLED ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hsmmc_context_restore (struct omap_hsmmc_host*) ; 

__attribute__((used)) static int omap_hsmmc_disabled_to_enabled(struct omap_hsmmc_host *host)
{
	int err;

	err = clk_enable(host->fclk);
	if (err < 0)
		return err;

	omap_hsmmc_context_restore(host);
	host->dpm_state = ENABLED;

	dev_dbg(mmc_dev(host->mmc), "DISABLED -> ENABLED\n");

	return 0;
}