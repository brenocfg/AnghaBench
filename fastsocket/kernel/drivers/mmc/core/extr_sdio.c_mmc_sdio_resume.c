#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* driver; } ;
struct sdio_func {TYPE_2__ dev; } ;
struct mmc_host {TYPE_3__* card; int /*<<< orphan*/  ocr; } ;
struct dev_pm_ops {int (* resume ) (TYPE_2__*) ;} ;
struct TYPE_6__ {int sdio_funcs; struct sdio_func** sdio_func; } ;
struct TYPE_4__ {struct dev_pm_ops* pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 
 int mmc_sdio_init_card (struct mmc_host*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ sdio_func_present (struct sdio_func*) ; 
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static int mmc_sdio_resume(struct mmc_host *host)
{
	int i, err;

	BUG_ON(!host);
	BUG_ON(!host->card);

	/* Basic card reinitialization. */
	mmc_claim_host(host);
	err = mmc_sdio_init_card(host, host->ocr, host->card);
	mmc_release_host(host);

	/*
	 * If the card looked to be the same as before suspending, then
	 * we proceed to resume all card functions.  If one of them returns
	 * an error then we simply return that error to the core and the
	 * card will be redetected as new.  It is the responsibility of
	 * the function driver to perform further tests with the extra
	 * knowledge it has of the card to confirm the card is indeed the
	 * same as before suspending (same MAC address for network cards,
	 * etc.) and return an error otherwise.
	 */
	for (i = 0; !err && i < host->card->sdio_funcs; i++) {
		struct sdio_func *func = host->card->sdio_func[i];
		if (func && sdio_func_present(func) && func->dev.driver) {
			const struct dev_pm_ops *pmops = func->dev.driver->pm;
			err = pmops->resume(&func->dev);
		}
	}

	return err;
}