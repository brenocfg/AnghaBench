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
struct TYPE_2__ {unsigned int max_dtr; } ;
struct mmc_card {scalar_t__ type; TYPE_1__ cis; } ;

/* Variables and functions */
 scalar_t__ MMC_TYPE_SD_COMBO ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_card_highspeed (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_sd_get_max_clock (struct mmc_card*) ; 

__attribute__((used)) static unsigned mmc_sdio_get_max_clock(struct mmc_card *card)
{
	unsigned max_dtr;

	if (mmc_card_highspeed(card)) {
		/*
		 * The SDIO specification doesn't mention how
		 * the CIS transfer speed register relates to
		 * high-speed, but it seems that 50 MHz is
		 * mandatory.
		 */
		max_dtr = 50000000;
	} else {
		max_dtr = card->cis.max_dtr;
	}

	if (card->type == MMC_TYPE_SD_COMBO)
		max_dtr = min(max_dtr, mmc_sd_get_max_clock(card));

	return max_dtr;
}