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
struct mmc_host {int caps; struct mmc_card* card; } ;
struct mmc_command {int arg; int flags; int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  sa_timeout; } ;
struct mmc_card {int rca; TYPE_1__ ext_csd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int MMC_CAP_WAIT_WHILE_BUSY ; 
 int MMC_CMD_AC ; 
 int MMC_RSP_R1B ; 
 int /*<<< orphan*/  MMC_SLEEP_AWAKE ; 
 int /*<<< orphan*/  memset (struct mmc_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_deselect_cards (struct mmc_host*) ; 
 int mmc_select_card (struct mmc_card*) ; 
 int mmc_wait_for_cmd (struct mmc_host*,struct mmc_command*,int /*<<< orphan*/ ) ; 

int mmc_card_sleepawake(struct mmc_host *host, int sleep)
{
	struct mmc_command cmd;
	struct mmc_card *card = host->card;
	int err;

	if (sleep)
		mmc_deselect_cards(host);

	memset(&cmd, 0, sizeof(struct mmc_command));

	cmd.opcode = MMC_SLEEP_AWAKE;
	cmd.arg = card->rca << 16;
	if (sleep)
		cmd.arg |= 1 << 15;

	cmd.flags = MMC_RSP_R1B | MMC_CMD_AC;
	err = mmc_wait_for_cmd(host, &cmd, 0);
	if (err)
		return err;

	/*
	 * If the host does not wait while the card signals busy, then we will
	 * will have to wait the sleep/awake timeout.  Note, we cannot use the
	 * SEND_STATUS command to poll the status because that command (and most
	 * others) is invalid while the card sleeps.
	 */
	if (!(host->caps & MMC_CAP_WAIT_WHILE_BUSY))
		mmc_delay(DIV_ROUND_UP(card->ext_csd.sa_timeout, 10000));

	if (!sleep)
		err = mmc_select_card(card);

	return err;
}