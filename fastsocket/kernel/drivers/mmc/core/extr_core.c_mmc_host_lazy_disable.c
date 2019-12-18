#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mmc_host {int caps; scalar_t__ disable_delay; int /*<<< orphan*/  disable; int /*<<< orphan*/  enabled; scalar_t__ nesting_cnt; scalar_t__ en_dis_recurs; } ;

/* Variables and functions */
 int MMC_CAP_DISABLE ; 
 int mmc_host_do_disable (struct mmc_host*,int) ; 
 int /*<<< orphan*/  mmc_schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (scalar_t__) ; 

int mmc_host_lazy_disable(struct mmc_host *host)
{
	if (!(host->caps & MMC_CAP_DISABLE))
		return 0;

	if (host->en_dis_recurs)
		return 0;

	if (--host->nesting_cnt)
		return 0;

	if (!host->enabled)
		return 0;

	if (host->disable_delay) {
		mmc_schedule_delayed_work(&host->disable,
				msecs_to_jiffies(host->disable_delay));
		return 0;
	} else
		return mmc_host_do_disable(host, 1);
}