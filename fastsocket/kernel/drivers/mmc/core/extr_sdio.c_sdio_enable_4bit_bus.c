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
struct TYPE_4__ {int bus_widths; } ;
struct mmc_card {scalar_t__ type; TYPE_2__ scr; TYPE_1__* host; } ;
struct TYPE_3__ {int caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_BUS_WIDTH_1 ; 
 int /*<<< orphan*/  MMC_BUS_WIDTH_4 ; 
 int MMC_CAP_4_BIT_DATA ; 
 scalar_t__ MMC_TYPE_SDIO ; 
 int SD_SCR_BUS_WIDTH_4 ; 
 int mmc_app_set_bus_width (struct mmc_card*,int /*<<< orphan*/ ) ; 
 int sdio_enable_wide (struct mmc_card*) ; 

__attribute__((used)) static int sdio_enable_4bit_bus(struct mmc_card *card)
{
	int err;

	if (card->type == MMC_TYPE_SDIO)
		return sdio_enable_wide(card);

	if ((card->host->caps & MMC_CAP_4_BIT_DATA) &&
		(card->scr.bus_widths & SD_SCR_BUS_WIDTH_4)) {
		err = mmc_app_set_bus_width(card, MMC_BUS_WIDTH_4);
		if (err)
			return err;
	} else
		return 0;

	err = sdio_enable_wide(card);
	if (err <= 0)
		mmc_app_set_bus_width(card, MMC_BUS_WIDTH_1);

	return err;
}