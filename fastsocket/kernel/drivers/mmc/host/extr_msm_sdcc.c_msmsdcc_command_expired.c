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
struct TYPE_5__ {int /*<<< orphan*/ * cmd; struct mmc_request* mrq; } ;
struct TYPE_4__ {int /*<<< orphan*/  sg; } ;
struct msmsdcc_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  lock; TYPE_2__ curr; scalar_t__ base; TYPE_1__ dma; } ;
struct mmc_request {TYPE_3__* cmd; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 scalar_t__ MMCICOMMAND ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  msmsdcc_stop_data (struct msmsdcc_host*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,struct mmc_request*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
msmsdcc_command_expired(unsigned long _data)
{
	struct msmsdcc_host	*host = (struct msmsdcc_host *) _data;
	struct mmc_request	*mrq;
	unsigned long		flags;

	spin_lock_irqsave(&host->lock, flags);
	mrq = host->curr.mrq;

	if (!mrq) {
		pr_info("%s: Command expiry misfire\n",
			mmc_hostname(host->mmc));
		spin_unlock_irqrestore(&host->lock, flags);
		return;
	}

	pr_err("%s: Command timeout (%p %p %p %p)\n",
	       mmc_hostname(host->mmc), mrq, mrq->cmd,
	       mrq->data, host->dma.sg);

	mrq->cmd->error = -ETIMEDOUT;
	msmsdcc_stop_data(host);

	writel(0, host->base + MMCICOMMAND);

	host->curr.mrq = NULL;
	host->curr.cmd = NULL;

	spin_unlock_irqrestore(&host->lock, flags);
	mmc_request_done(host->mmc, mrq);
}