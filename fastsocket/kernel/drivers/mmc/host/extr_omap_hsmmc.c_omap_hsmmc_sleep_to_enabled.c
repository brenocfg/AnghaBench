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
struct omap_hsmmc_host {scalar_t__ dpm_state; int /*<<< orphan*/  mmc; int /*<<< orphan*/  vdd; int /*<<< orphan*/  slot_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  fclk; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_sleep ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ CARDSLEEP ; 
 scalar_t__ ENABLED ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mmc_card_awake (int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_card_can_sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_release_host (int /*<<< orphan*/ ) ; 
 TYPE_1__ mmc_slot (struct omap_hsmmc_host*) ; 
 int /*<<< orphan*/  mmc_try_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hsmmc_context_restore (struct omap_hsmmc_host*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int omap_hsmmc_sleep_to_enabled(struct omap_hsmmc_host *host)
{
	if (!mmc_try_claim_host(host->mmc))
		return 0;

	clk_enable(host->fclk);
	omap_hsmmc_context_restore(host);
	if (mmc_slot(host).set_sleep)
		mmc_slot(host).set_sleep(host->dev, host->slot_id, 0,
			 host->vdd, host->dpm_state == CARDSLEEP);
	if (mmc_card_can_sleep(host->mmc))
		mmc_card_awake(host->mmc);

	dev_dbg(mmc_dev(host->mmc), "%s -> ENABLED\n",
		host->dpm_state == CARDSLEEP ? "CARDSLEEP" : "REGSLEEP");

	host->dpm_state = ENABLED;

	mmc_release_host(host->mmc);

	return 0;
}