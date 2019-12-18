#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct omap_hsmmc_host {scalar_t__ dpm_state; TYPE_1__* mmc; int /*<<< orphan*/  power_mode; scalar_t__ vdd; int /*<<< orphan*/  slot_id; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_power ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* get_cover_state ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ card_detect; } ;
struct TYPE_5__ {int caps; } ;

/* Variables and functions */
 scalar_t__ CARDSLEEP ; 
 int MMC_CAP_NONREMOVABLE ; 
 int /*<<< orphan*/  MMC_POWER_OFF ; 
 scalar_t__ OFF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_release_host (TYPE_1__*) ; 
 TYPE_2__ mmc_slot (struct omap_hsmmc_host*) ; 
 int /*<<< orphan*/  mmc_try_claim_host (TYPE_1__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hsmmc_sleep_to_off(struct omap_hsmmc_host *host)
{
	if (!mmc_try_claim_host(host->mmc))
		return 0;

	if (!((host->mmc->caps & MMC_CAP_NONREMOVABLE) ||
	      mmc_slot(host).card_detect ||
	      (mmc_slot(host).get_cover_state &&
	       mmc_slot(host).get_cover_state(host->dev, host->slot_id)))) {
		mmc_release_host(host->mmc);
		return 0;
	}

	mmc_slot(host).set_power(host->dev, host->slot_id, 0, 0);
	host->vdd = 0;
	host->power_mode = MMC_POWER_OFF;

	dev_dbg(mmc_dev(host->mmc), "%s -> OFF\n",
		host->dpm_state == CARDSLEEP ? "CARDSLEEP" : "REGSLEEP");

	host->dpm_state = OFF;

	mmc_release_host(host->mmc);

	return 0;
}