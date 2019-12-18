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
struct mmc_host {int claimed; scalar_t__ claimer; int claim_cnt; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ current ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mmc_try_claim_host(struct mmc_host *host)
{
	int claimed_host = 0;
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);
	if (!host->claimed || host->claimer == current) {
		host->claimed = 1;
		host->claimer = current;
		host->claim_cnt += 1;
		claimed_host = 1;
	}
	spin_unlock_irqrestore(&host->lock, flags);
	return claimed_host;
}