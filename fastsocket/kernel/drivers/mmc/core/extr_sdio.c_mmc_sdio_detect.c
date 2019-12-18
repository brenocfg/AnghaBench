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
struct mmc_host {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_detach_bus (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_sdio_remove (struct mmc_host*) ; 
 int mmc_select_card (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmc_sdio_detect(struct mmc_host *host)
{
	int err;

	BUG_ON(!host);
	BUG_ON(!host->card);

	mmc_claim_host(host);

	/*
	 * Just check if our card has been removed.
	 */
	err = mmc_select_card(host->card);

	mmc_release_host(host);

	if (err) {
		mmc_sdio_remove(host);

		mmc_claim_host(host);
		mmc_detach_bus(host);
		mmc_release_host(host);
	}
}