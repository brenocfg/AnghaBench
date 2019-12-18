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
struct mmc_request {TYPE_1__* cmd; TYPE_1__* stop; } ;
struct mmc_host {int dummy; } ;
struct cb710_slot {int dummy; } ;
struct cb710_mmc_reader {int /*<<< orphan*/  finish_req_tasklet; struct mmc_request* mrq; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB710_MMC_IE_TEST_MASK ; 
 int /*<<< orphan*/  ENOMEDIUM ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_mmc_command (struct mmc_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  cb710_mmc_enable_irq (struct cb710_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cb710_mmc_is_card_inserted (struct cb710_slot*) ; 
 struct cb710_slot* cb710_mmc_to_slot (struct mmc_host*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct cb710_mmc_reader* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cb710_mmc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct cb710_slot *slot = cb710_mmc_to_slot(mmc);
	struct cb710_mmc_reader *reader = mmc_priv(mmc);

	WARN_ON(reader->mrq != NULL);

	reader->mrq = mrq;
	cb710_mmc_enable_irq(slot, CB710_MMC_IE_TEST_MASK, 0);

	if (cb710_mmc_is_card_inserted(slot)) {
		if (!cb710_mmc_command(mmc, mrq->cmd) && mrq->stop)
			cb710_mmc_command(mmc, mrq->stop);
		mdelay(1);
	} else {
		mrq->cmd->error = -ENOMEDIUM;
	}

	tasklet_schedule(&reader->finish_req_tasklet);
}