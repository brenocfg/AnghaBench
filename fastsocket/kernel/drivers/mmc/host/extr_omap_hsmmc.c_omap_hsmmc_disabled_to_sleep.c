#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct omap_hsmmc_host {int dpm_state; int /*<<< orphan*/  slot_id; int /*<<< orphan*/  dev; TYPE_1__* mmc; int /*<<< orphan*/  fclk; } ;
struct TYPE_8__ {scalar_t__ (* get_cover_state ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ card_detect; int /*<<< orphan*/  (* set_sleep ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_7__ {int caps; } ;

/* Variables and functions */
 int CARDSLEEP ; 
 int MMC_CAP_NONREMOVABLE ; 
 int /*<<< orphan*/  OMAP_MMC_OFF_TIMEOUT ; 
 int REGSLEEP ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ mmc_card_can_sleep (TYPE_1__*) ; 
 int mmc_card_sleep (TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_release_host (TYPE_1__*) ; 
 TYPE_2__ mmc_slot (struct omap_hsmmc_host*) ; 
 int /*<<< orphan*/  mmc_try_claim_host (TYPE_1__*) ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hsmmc_context_restore (struct omap_hsmmc_host*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hsmmc_disabled_to_sleep(struct omap_hsmmc_host *host)
{
	int err, new_state;

	if (!mmc_try_claim_host(host->mmc))
		return 0;

	clk_enable(host->fclk);
	omap_hsmmc_context_restore(host);
	if (mmc_card_can_sleep(host->mmc)) {
		err = mmc_card_sleep(host->mmc);
		if (err < 0) {
			clk_disable(host->fclk);
			mmc_release_host(host->mmc);
			return err;
		}
		new_state = CARDSLEEP;
	} else {
		new_state = REGSLEEP;
	}
	if (mmc_slot(host).set_sleep)
		mmc_slot(host).set_sleep(host->dev, host->slot_id, 1, 0,
					 new_state == CARDSLEEP);
	/* FIXME: turn off bus power and perhaps interrupts too */
	clk_disable(host->fclk);
	host->dpm_state = new_state;

	mmc_release_host(host->mmc);

	dev_dbg(mmc_dev(host->mmc), "DISABLED -> %s\n",
		host->dpm_state == CARDSLEEP ? "CARDSLEEP" : "REGSLEEP");

	if ((host->mmc->caps & MMC_CAP_NONREMOVABLE) ||
	    mmc_slot(host).card_detect ||
	    (mmc_slot(host).get_cover_state &&
	     mmc_slot(host).get_cover_state(host->dev, host->slot_id)))
		return msecs_to_jiffies(OMAP_MMC_OFF_TIMEOUT);

	return 0;
}