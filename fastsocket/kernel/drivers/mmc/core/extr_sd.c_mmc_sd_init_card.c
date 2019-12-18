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
struct mmc_host {int caps; struct mmc_card* card; TYPE_1__* ops; int /*<<< orphan*/  claimed; } ;
struct TYPE_4__ {int bus_widths; } ;
struct mmc_card {TYPE_2__ scr; int /*<<< orphan*/  rca; int /*<<< orphan*/  raw_cid; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  cid ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable_preset_value ) (struct mmc_host*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct mmc_card*) ; 
 int /*<<< orphan*/  MMC_BUSMODE_PUSHPULL ; 
 int /*<<< orphan*/  MMC_BUS_WIDTH_4 ; 
 int MMC_CAP_4_BIT_DATA ; 
 int /*<<< orphan*/  MMC_TYPE_SD ; 
 int PTR_ERR (struct mmc_card*) ; 
 int SD_ROCR_S18A ; 
 int SD_SCR_BUS_WIDTH_4 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 struct mmc_card* mmc_alloc_card (struct mmc_host*,int /*<<< orphan*/ *) ; 
 int mmc_app_set_bus_width (struct mmc_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_decode_cid (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_host_is_spi (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_card (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_sd_card_set_uhs (struct mmc_card*) ; 
 int mmc_sd_get_cid (struct mmc_host*,int,int*,int*) ; 
 int mmc_sd_get_csd (struct mmc_host*,struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_sd_get_max_clock (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_sd_go_highspeed (struct mmc_card*) ; 
 int mmc_sd_init_uhs_card (struct mmc_card*) ; 
 int mmc_sd_setup_card (struct mmc_host*,struct mmc_card*,int /*<<< orphan*/ ) ; 
 int mmc_sd_switch_hs (struct mmc_card*) ; 
 int mmc_select_card (struct mmc_card*) ; 
 int mmc_send_relative_addr (struct mmc_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_set_bus_mode (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_set_bus_width (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_set_clock (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_type ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*,int) ; 

__attribute__((used)) static int mmc_sd_init_card(struct mmc_host *host, u32 ocr,
	struct mmc_card *oldcard)
{
	struct mmc_card *card;
	int err;
	u32 cid[4];
	u32 rocr = 0;

	BUG_ON(!host);
	WARN_ON(!host->claimed);

	err = mmc_sd_get_cid(host, ocr, cid, &rocr);
	if (err)
		return err;

	if (oldcard) {
		if (memcmp(cid, oldcard->raw_cid, sizeof(cid)) != 0)
			return -ENOENT;

		card = oldcard;
	} else {
		/*
		 * Allocate card structure.
		 */
		card = mmc_alloc_card(host, &sd_type);
		if (IS_ERR(card))
			return PTR_ERR(card);

		card->type = MMC_TYPE_SD;
		memcpy(card->raw_cid, cid, sizeof(card->raw_cid));
	}

	/*
	 * For native busses:  get card RCA and quit open drain mode.
	 */
	if (!mmc_host_is_spi(host)) {
		err = mmc_send_relative_addr(host, &card->rca);
		if (err)
			return err;

		mmc_set_bus_mode(host, MMC_BUSMODE_PUSHPULL);
	}

	if (!oldcard) {
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
			return err;
	}

	err = mmc_sd_setup_card(host, card, oldcard != NULL);
	if (err)
		goto free_card;

	/* Initialization sequence for UHS-I cards */
	if (rocr & SD_ROCR_S18A) {
		err = mmc_sd_init_uhs_card(card);
		if (err)
			goto free_card;

		/* Card is an ultra-high-speed card */
		mmc_sd_card_set_uhs(card);

		/*
		 * Since initialization is now complete, enable preset
		 * value registers for UHS-I cards.
		 */
		if (host->ops->enable_preset_value)
			host->ops->enable_preset_value(host, true);
	} else {
		/*
		 * Attempt to change to high-speed (if supported)
		 */
		err = mmc_sd_switch_hs(card);
		if (err > 0)
			mmc_sd_go_highspeed(card);
		else if (err)
			goto free_card;

		/*
		 * Set bus speed.
		 */
		mmc_set_clock(host, mmc_sd_get_max_clock(card));

		/*
		 * Switch to wider bus (if supported).
		 */
		if ((host->caps & MMC_CAP_4_BIT_DATA) &&
			(card->scr.bus_widths & SD_SCR_BUS_WIDTH_4)) {
			err = mmc_app_set_bus_width(card, MMC_BUS_WIDTH_4);
			if (err)
				goto free_card;

			mmc_set_bus_width(host, MMC_BUS_WIDTH_4);
		}
	}

	host->card = card;
	return 0;

free_card:
	if (!oldcard)
		mmc_remove_card(card);

	return err;
}