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
struct mmc_host {TYPE_1__* card; int /*<<< orphan*/  ocr; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_STATE_HIGHSPEED ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_init_card (struct mmc_host*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 

__attribute__((used)) static void mmc_power_restore(struct mmc_host *host)
{
	host->card->state &= ~MMC_STATE_HIGHSPEED;
	mmc_claim_host(host);
	mmc_init_card(host, host->ocr, host->card);
	mmc_release_host(host);
}