#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mmc_host {int ocr; struct mmc_card* card; int /*<<< orphan*/  claimed; } ;
struct TYPE_4__ {int /*<<< orphan*/ * type; } ;
struct TYPE_3__ {scalar_t__ vendor; scalar_t__ device; } ;
struct mmc_card {scalar_t__ type; int /*<<< orphan*/  host; TYPE_2__ dev; TYPE_1__ cis; int /*<<< orphan*/  rca; int /*<<< orphan*/  raw_cid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct mmc_card*) ; 
 int /*<<< orphan*/  MMC_BUSMODE_PUSHPULL ; 
 int /*<<< orphan*/  MMC_BUS_WIDTH_4 ; 
 scalar_t__ MMC_TYPE_SDIO ; 
 scalar_t__ MMC_TYPE_SD_COMBO ; 
 int PTR_ERR (struct mmc_card*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mmc_card* mmc_alloc_card (struct mmc_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_decode_cid (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_go_idle (struct mmc_host*) ; 
 scalar_t__ mmc_host_is_spi (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_card (struct mmc_card*) ; 
 int mmc_sd_get_cid (struct mmc_host*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mmc_sd_get_csd (struct mmc_host*,struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_sd_go_highspeed (struct mmc_card*) ; 
 int mmc_sd_setup_card (struct mmc_host*,struct mmc_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_sdio_get_max_clock (struct mmc_card*) ; 
 int mmc_select_card (struct mmc_card*) ; 
 int mmc_send_io_op_cond (struct mmc_host*,int,int*) ; 
 int mmc_send_relative_addr (struct mmc_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_set_bus_mode (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_set_bus_width (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_set_clock (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int mmc_spi_set_crc (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_type ; 
 int sdio_disable_cd (struct mmc_card*) ; 
 int sdio_enable_4bit_bus (struct mmc_card*) ; 
 int sdio_enable_hs (struct mmc_card*) ; 
 int sdio_read_cccr (struct mmc_card*) ; 
 int sdio_read_common_cis (struct mmc_card*) ; 
 int /*<<< orphan*/  use_spi_crc ; 

__attribute__((used)) static int mmc_sdio_init_card(struct mmc_host *host, u32 ocr,
			      struct mmc_card *oldcard)
{
	struct mmc_card *card;
	int err;

	BUG_ON(!host);
	WARN_ON(!host->claimed);

	/*
	 * Inform the card of the voltage
	 */
	err = mmc_send_io_op_cond(host, host->ocr, &ocr);
	if (err)
		goto err;

	/*
	 * For SPI, enable CRC as appropriate.
	 */
	if (mmc_host_is_spi(host)) {
		err = mmc_spi_set_crc(host, use_spi_crc);
		if (err)
			goto err;
	}

	/*
	 * Allocate card structure.
	 */
	card = mmc_alloc_card(host, NULL);
	if (IS_ERR(card)) {
		err = PTR_ERR(card);
		goto err;
	}

	err = mmc_sd_get_cid(host, host->ocr & ocr, card->raw_cid, NULL);

	if (!err) {
		card->type = MMC_TYPE_SD_COMBO;

		if (oldcard && (oldcard->type != MMC_TYPE_SD_COMBO ||
		    memcmp(card->raw_cid, oldcard->raw_cid, sizeof(card->raw_cid)) != 0)) {
			mmc_remove_card(card);
			return -ENOENT;
		}
	} else {
		card->type = MMC_TYPE_SDIO;

		if (oldcard && oldcard->type != MMC_TYPE_SDIO) {
			mmc_remove_card(card);
			return -ENOENT;
		}
	}

	/*
	 * For native busses:  set card RCA and quit open drain mode.
	 */
	if (!mmc_host_is_spi(host)) {
		err = mmc_send_relative_addr(host, &card->rca);
		if (err)
			goto remove;

		mmc_set_bus_mode(host, MMC_BUSMODE_PUSHPULL);
	}

	/*
	 * Read CSD, before selecting the card
	 */
	if (!oldcard && card->type == MMC_TYPE_SD_COMBO) {
		err = mmc_sd_get_csd(host, card);
		if (err)
			return err;

		mmc_decode_cid(card);
	}

	/*
	 * Select card, as all following commands rely on that.
	 */
	if (!mmc_host_is_spi(host)) {
		err = mmc_select_card(card);
		if (err)
			goto remove;
	}

	/*
	 * Read the common registers.
	 */
	err = sdio_read_cccr(card);
	if (err)
		goto remove;

	/*
	 * Read the common CIS tuples.
	 */
	err = sdio_read_common_cis(card);
	if (err)
		goto remove;

	if (oldcard) {
		int same = (card->cis.vendor == oldcard->cis.vendor &&
			    card->cis.device == oldcard->cis.device);
		mmc_remove_card(card);
		if (!same)
			return -ENOENT;

		card = oldcard;
		return 0;
	}

	if (card->type == MMC_TYPE_SD_COMBO) {
		err = mmc_sd_setup_card(host, card, oldcard != NULL);
		/* handle as SDIO-only card if memory init failed */
		if (err) {
			mmc_go_idle(host);
			if (mmc_host_is_spi(host))
				/* should not fail, as it worked previously */
				mmc_spi_set_crc(host, use_spi_crc);
			card->type = MMC_TYPE_SDIO;
		} else
			card->dev.type = &sd_type;
	}

	/*
	 * If needed, disconnect card detection pull-up resistor.
	 */
	err = sdio_disable_cd(card);
	if (err)
		goto remove;

	/*
	 * Switch to high-speed (if supported).
	 */
	err = sdio_enable_hs(card);
	if (err > 0)
		mmc_sd_go_highspeed(card);
	else if (err)
		goto remove;

	/*
	 * Change to the card's maximum speed.
	 */
	mmc_set_clock(host, mmc_sdio_get_max_clock(card));

	/*
	 * Switch to wider bus (if supported).
	 */
	err = sdio_enable_4bit_bus(card);
	if (err > 0)
		mmc_set_bus_width(card->host, MMC_BUS_WIDTH_4);
	else if (err)
		goto remove;

	if (!oldcard)
		host->card = card;
	return 0;

remove:
	if (!oldcard)
		mmc_remove_card(card);

err:
	return err;
}