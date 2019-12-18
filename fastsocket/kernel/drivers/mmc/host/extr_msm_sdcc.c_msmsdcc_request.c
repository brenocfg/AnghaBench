#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  cmdpoll_misses; int /*<<< orphan*/  cmdpoll_hits; int /*<<< orphan*/  reqs; } ;
struct TYPE_5__ {struct mmc_request* mrq; } ;
struct msmsdcc_host {scalar_t__ pwr; int /*<<< orphan*/  lock; int /*<<< orphan*/  command_timer; TYPE_2__ stats; scalar_t__ base; scalar_t__ cmdpoll; TYPE_1__ curr; scalar_t__ eject; } ;
struct mmc_request {TYPE_4__* cmd; TYPE_3__* data; } ;
struct mmc_host {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  error; } ;
struct TYPE_7__ {int flags; int bytes_xfered; int blksz; int blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SPINMAX ; 
 int /*<<< orphan*/  ENOMEDIUM ; 
 scalar_t__ HZ ; 
 int MCI_CMDCRCFAIL ; 
 int MCI_CMDRESPEND ; 
 int MCI_CMDTIMEOUT ; 
 scalar_t__ MMCICLEAR ; 
 scalar_t__ MMCISTATUS ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ jiffies ; 
 struct msmsdcc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msmsdcc_do_cmdirq (struct msmsdcc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msmsdcc_spin_on_status (struct msmsdcc_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msmsdcc_start_command (struct msmsdcc_host*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msmsdcc_start_data (struct msmsdcc_host*,TYPE_3__*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void
msmsdcc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct msmsdcc_host *host = mmc_priv(mmc);
	unsigned long flags;

	WARN_ON(host->curr.mrq != NULL);
	WARN_ON(host->pwr == 0);

	spin_lock_irqsave(&host->lock, flags);

	host->stats.reqs++;

	if (host->eject) {
		if (mrq->data && !(mrq->data->flags & MMC_DATA_READ)) {
			mrq->cmd->error = 0;
			mrq->data->bytes_xfered = mrq->data->blksz *
						  mrq->data->blocks;
		} else
			mrq->cmd->error = -ENOMEDIUM;

		spin_unlock_irqrestore(&host->lock, flags);
		mmc_request_done(mmc, mrq);
		return;
	}

	host->curr.mrq = mrq;

	if (mrq->data && mrq->data->flags & MMC_DATA_READ)
		msmsdcc_start_data(host, mrq->data);

	msmsdcc_start_command(host, mrq->cmd, 0);

	if (host->cmdpoll && !msmsdcc_spin_on_status(host,
				MCI_CMDRESPEND|MCI_CMDCRCFAIL|MCI_CMDTIMEOUT,
				CMD_SPINMAX)) {
		uint32_t status = readl(host->base + MMCISTATUS);
		msmsdcc_do_cmdirq(host, status);
		writel(MCI_CMDRESPEND | MCI_CMDCRCFAIL | MCI_CMDTIMEOUT,
		       host->base + MMCICLEAR);
		host->stats.cmdpoll_hits++;
	} else {
		host->stats.cmdpoll_misses++;
		mod_timer(&host->command_timer, jiffies + HZ);
	}
	spin_unlock_irqrestore(&host->lock, flags);
}