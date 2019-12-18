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
struct mmc_data {int timeout_ns; unsigned int timeout_clks; int flags; } ;
struct TYPE_4__ {unsigned int r2w_factor; unsigned int tacc_ns; unsigned int tacc_clks; } ;
struct mmc_card {TYPE_3__* host; TYPE_1__ csd; } ;
struct TYPE_5__ {int clock; } ;
struct TYPE_6__ {TYPE_2__ ios; } ;

/* Variables and functions */
 int MMC_DATA_WRITE ; 
 scalar_t__ mmc_card_blockaddr (struct mmc_card const*) ; 
 scalar_t__ mmc_card_sd (struct mmc_card const*) ; 
 scalar_t__ mmc_card_sdio (struct mmc_card const*) ; 
 scalar_t__ mmc_host_is_spi (TYPE_3__*) ; 

void mmc_set_data_timeout(struct mmc_data *data, const struct mmc_card *card)
{
	unsigned int mult;

	/*
	 * SDIO cards only define an upper 1 s limit on access.
	 */
	if (mmc_card_sdio(card)) {
		data->timeout_ns = 1000000000;
		data->timeout_clks = 0;
		return;
	}

	/*
	 * SD cards use a 100 multiplier rather than 10
	 */
	mult = mmc_card_sd(card) ? 100 : 10;

	/*
	 * Scale up the multiplier (and therefore the timeout) by
	 * the r2w factor for writes.
	 */
	if (data->flags & MMC_DATA_WRITE)
		mult <<= card->csd.r2w_factor;

	data->timeout_ns = card->csd.tacc_ns * mult;
	data->timeout_clks = card->csd.tacc_clks * mult;

	/*
	 * SD cards also have an upper limit on the timeout.
	 */
	if (mmc_card_sd(card)) {
		unsigned int timeout_us, limit_us;

		timeout_us = data->timeout_ns / 1000;
		timeout_us += data->timeout_clks * 1000 /
			(card->host->ios.clock / 1000);

		if (data->flags & MMC_DATA_WRITE)
			/*
			 * The limit is really 250 ms, but that is
			 * insufficient for some crappy cards.
			 */
			limit_us = 300000;
		else
			limit_us = 100000;

		/*
		 * SDHC cards always use these fixed values.
		 */
		if (timeout_us > limit_us || mmc_card_blockaddr(card)) {
			data->timeout_ns = limit_us * 1000;
			data->timeout_clks = 0;
		}
	}
	/*
	 * Some cards need very high timeouts if driven in SPI mode.
	 * The worst observed timeout was 900ms after writing a
	 * continuous stream of data until the internal logic
	 * overflowed.
	 */
	if (mmc_host_is_spi(card->host)) {
		if (data->flags & MMC_DATA_WRITE) {
			if (data->timeout_ns < 1000000000)
				data->timeout_ns = 1000000000;	/* 1s */
		} else {
			if (data->timeout_ns < 100000000)
				data->timeout_ns =  100000000;	/* 100ms */
		}
	}
}