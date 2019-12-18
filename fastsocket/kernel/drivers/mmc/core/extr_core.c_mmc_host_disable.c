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
struct mmc_host {int caps; int /*<<< orphan*/  enabled; scalar_t__ nesting_cnt; scalar_t__ en_dis_recurs; } ;

/* Variables and functions */
 int MMC_CAP_DISABLE ; 
 int mmc_host_do_disable (struct mmc_host*,int /*<<< orphan*/ ) ; 

int mmc_host_disable(struct mmc_host *host)
{
	int err;

	if (!(host->caps & MMC_CAP_DISABLE))
		return 0;

	if (host->en_dis_recurs)
		return 0;

	if (--host->nesting_cnt)
		return 0;

	if (!host->enabled)
		return 0;

	err = mmc_host_do_disable(host, 0);
	return err;
}