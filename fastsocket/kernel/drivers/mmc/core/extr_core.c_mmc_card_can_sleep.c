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
struct mmc_host {struct mmc_card* card; } ;
struct TYPE_2__ {int rev; } ;
struct mmc_card {TYPE_1__ ext_csd; } ;

/* Variables and functions */
 scalar_t__ mmc_card_mmc (struct mmc_card*) ; 

int mmc_card_can_sleep(struct mmc_host *host)
{
	struct mmc_card *card = host->card;

	if (card && mmc_card_mmc(card) && card->ext_csd.rev >= 3)
		return 1;
	return 0;
}