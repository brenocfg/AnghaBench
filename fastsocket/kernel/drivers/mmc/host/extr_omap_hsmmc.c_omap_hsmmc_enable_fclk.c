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
struct omap_hsmmc_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  fclk; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 struct omap_hsmmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  omap_hsmmc_context_restore (struct omap_hsmmc_host*) ; 

__attribute__((used)) static int omap_hsmmc_enable_fclk(struct mmc_host *mmc)
{
	struct omap_hsmmc_host *host = mmc_priv(mmc);
	int err;

	err = clk_enable(host->fclk);
	if (err)
		return err;
	dev_dbg(mmc_dev(host->mmc), "mmc_fclk: enabled\n");
	omap_hsmmc_context_restore(host);
	return 0;
}