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
struct mmc_host {int en_dis_recurs; scalar_t__ enabled; int /*<<< orphan*/  disable; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* disable ) (struct mmc_host*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct mmc_host*,int) ; 

__attribute__((used)) static int mmc_host_do_disable(struct mmc_host *host, int lazy)
{
	if (host->ops->disable) {
		int err;

		host->en_dis_recurs = 1;
		err = host->ops->disable(host, lazy);
		host->en_dis_recurs = 0;

		if (err < 0) {
			pr_debug("%s: disable error %d\n",
				 mmc_hostname(host), err);
			return err;
		}
		if (err > 0) {
			unsigned long delay = msecs_to_jiffies(err);

			mmc_schedule_delayed_work(&host->disable, delay);
		}
	}
	host->enabled = 0;
	return 0;
}