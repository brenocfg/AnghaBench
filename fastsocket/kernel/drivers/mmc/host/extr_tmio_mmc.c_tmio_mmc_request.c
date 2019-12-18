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
struct tmio_mmc_host {struct mmc_request* mrq; } ;
struct mmc_request {TYPE_1__* cmd; int /*<<< orphan*/  data; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int error; } ;

/* Variables and functions */
 struct tmio_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int tmio_mmc_start_command (struct tmio_mmc_host*,TYPE_1__*) ; 
 int tmio_mmc_start_data (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tmio_mmc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct tmio_mmc_host *host = mmc_priv(mmc);
	int ret;

	if (host->mrq)
		pr_debug("request not null\n");

	host->mrq = mrq;

	if (mrq->data) {
		ret = tmio_mmc_start_data(host, mrq->data);
		if (ret)
			goto fail;
	}

	ret = tmio_mmc_start_command(host, mrq->cmd);

	if (!ret)
		return;

fail:
	mrq->cmd->error = ret;
	mmc_request_done(mmc, mrq);
}