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
struct mmc_host {int removed; int caps; int /*<<< orphan*/  card; TYPE_1__* bus_ops; int /*<<< orphan*/  bus_dead; int /*<<< orphan*/  detect; int /*<<< orphan*/  disable; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int MMC_CAP_DISABLE ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_bus_get (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_bus_put (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_detach_bus (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_flush_scheduled_work () ; 
 int /*<<< orphan*/  mmc_power_off (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*) ; 

void mmc_stop_host(struct mmc_host *host)
{
#ifdef CONFIG_MMC_DEBUG
	unsigned long flags;
	spin_lock_irqsave(&host->lock, flags);
	host->removed = 1;
	spin_unlock_irqrestore(&host->lock, flags);
#endif

	if (host->caps & MMC_CAP_DISABLE)
		cancel_delayed_work(&host->disable);
	cancel_delayed_work(&host->detect);
	mmc_flush_scheduled_work();

	mmc_bus_get(host);
	if (host->bus_ops && !host->bus_dead) {
		if (host->bus_ops->remove)
			host->bus_ops->remove(host);

		mmc_claim_host(host);
		mmc_detach_bus(host);
		mmc_release_host(host);
		mmc_bus_put(host);
		return;
	}
	mmc_bus_put(host);

	BUG_ON(host->card);

	mmc_power_off(host);
}