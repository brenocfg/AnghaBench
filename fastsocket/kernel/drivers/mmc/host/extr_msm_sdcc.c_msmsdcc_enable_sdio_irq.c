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
typedef  int /*<<< orphan*/  u32 ;
struct msmsdcc_host {int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/  saved_irq0mask; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCI_SDIOINTOPERMASK ; 
 scalar_t__ MMCIMASK0 ; 
 struct msmsdcc_host* mmc_priv (struct mmc_host*) ; 
 int msmsdcc_sdioirq ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void msmsdcc_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
	struct msmsdcc_host *host = mmc_priv(mmc);
	unsigned long flags;
	u32 status;

	spin_lock_irqsave(&host->lock, flags);
	if (msmsdcc_sdioirq == 1) {
		status = readl(host->base + MMCIMASK0);
		if (enable)
			status |= MCI_SDIOINTOPERMASK;
		else
			status &= ~MCI_SDIOINTOPERMASK;
		host->saved_irq0mask = status;
		writel(status, host->base + MMCIMASK0);
	}
	spin_unlock_irqrestore(&host->lock, flags);
}