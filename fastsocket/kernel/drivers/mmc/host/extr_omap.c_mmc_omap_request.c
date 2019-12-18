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
struct mmc_request {int dummy; } ;
struct mmc_omap_slot {struct mmc_request* mrq; struct mmc_omap_host* host; } ;
struct mmc_omap_host {int /*<<< orphan*/  slot_lock; struct mmc_host* mmc; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_omap_select_slot (struct mmc_omap_slot*,int) ; 
 int /*<<< orphan*/  mmc_omap_start_request (struct mmc_omap_host*,struct mmc_request*) ; 
 struct mmc_omap_slot* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mmc_omap_request(struct mmc_host *mmc, struct mmc_request *req)
{
	struct mmc_omap_slot *slot = mmc_priv(mmc);
	struct mmc_omap_host *host = slot->host;
	unsigned long flags;

	spin_lock_irqsave(&host->slot_lock, flags);
	if (host->mmc != NULL) {
		BUG_ON(slot->mrq != NULL);
		slot->mrq = req;
		spin_unlock_irqrestore(&host->slot_lock, flags);
		return;
	} else
		host->mmc = mmc;
	spin_unlock_irqrestore(&host->slot_lock, flags);
	mmc_omap_select_slot(slot, 1);
	mmc_omap_start_request(host, req);
}