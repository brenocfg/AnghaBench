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
struct TYPE_4__ {scalar_t__ function; } ;
struct msmsdcc_host {int eject; unsigned int oldstat; TYPE_2__ timer; int /*<<< orphan*/  mmc; TYPE_1__* plat; } ;
struct TYPE_3__ {unsigned int (* status ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mmc_detect_change (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
msmsdcc_check_status(unsigned long data)
{
	struct msmsdcc_host *host = (struct msmsdcc_host *)data;
	unsigned int status;

	if (!host->plat->status) {
		mmc_detect_change(host->mmc, 0);
		goto out;
	}

	status = host->plat->status(mmc_dev(host->mmc));
	host->eject = !status;
	if (status ^ host->oldstat) {
		pr_info("%s: Slot status change detected (%d -> %d)\n",
			mmc_hostname(host->mmc), host->oldstat, status);
		if (status)
			mmc_detect_change(host->mmc, (5 * HZ) / 2);
		else
			mmc_detect_change(host->mmc, 0);
	}

	host->oldstat = status;

out:
	if (host->timer.function)
		mod_timer(&host->timer, jiffies + HZ);
}