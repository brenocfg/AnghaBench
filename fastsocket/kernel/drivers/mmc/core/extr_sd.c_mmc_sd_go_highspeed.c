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
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_TIMING_SD_HS ; 
 int /*<<< orphan*/  mmc_card_set_highspeed (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_set_timing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mmc_sd_go_highspeed(struct mmc_card *card)
{
	mmc_card_set_highspeed(card);
	mmc_set_timing(card->host, MMC_TIMING_SD_HS);
}