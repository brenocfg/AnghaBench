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
struct mmc_host {int caps; int en_dis_recurs; int enabled; TYPE_1__* ops; int /*<<< orphan*/  disable; int /*<<< orphan*/  nesting_cnt; } ;
struct TYPE_2__ {int (* enable ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int MMC_CAP_DISABLE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct mmc_host*) ; 

int mmc_host_enable(struct mmc_host *host)
{
	if (!(host->caps & MMC_CAP_DISABLE))
		return 0;

	if (host->en_dis_recurs)
		return 0;

	if (host->nesting_cnt++)
		return 0;

	cancel_delayed_work_sync(&host->disable);

	if (host->enabled)
		return 0;

	if (host->ops->enable) {
		int err;

		host->en_dis_recurs = 1;
		err = host->ops->enable(host);
		host->en_dis_recurs = 0;

		if (err) {
			pr_debug("%s: enable error %d\n",
				 mmc_hostname(host), err);
			return err;
		}
	}
	host->enabled = 1;
	return 0;
}