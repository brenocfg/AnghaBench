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
struct omap_hsmmc_host {int dpm_state; int /*<<< orphan*/  mmc; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
#define  CARDSLEEP 131 
#define  DISABLED 130 
 int EINVAL ; 
#define  ENABLED 129 
#define  REGSLEEP 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 struct omap_hsmmc_host* mmc_priv (struct mmc_host*) ; 
 int omap_hsmmc_disabled_to_sleep (struct omap_hsmmc_host*) ; 
 int omap_hsmmc_enabled_to_disabled (struct omap_hsmmc_host*) ; 
 int omap_hsmmc_sleep_to_off (struct omap_hsmmc_host*) ; 

__attribute__((used)) static int omap_hsmmc_disable(struct mmc_host *mmc, int lazy)
{
	struct omap_hsmmc_host *host = mmc_priv(mmc);

	switch (host->dpm_state) {
	case ENABLED: {
		int delay;

		delay = omap_hsmmc_enabled_to_disabled(host);
		if (lazy || delay < 0)
			return delay;
		return 0;
	}
	case DISABLED:
		return omap_hsmmc_disabled_to_sleep(host);
	case CARDSLEEP:
	case REGSLEEP:
		return omap_hsmmc_sleep_to_off(host);
	default:
		dev_dbg(mmc_dev(host->mmc), "UNKNOWN state\n");
		return -EINVAL;
	}
}