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
struct platform_device {int dummy; } ;
struct msmsdcc_host {int clks_on; scalar_t__ stat_irq; int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/  saved_irq0mask; int /*<<< orphan*/  clk; int /*<<< orphan*/  pclk; } ;
struct mmc_host {TYPE_1__* card; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ MMCIMASK0 ; 
 scalar_t__ MMC_TYPE_SDIO ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 
 struct mmc_host* mmc_get_drvdata (struct platform_device*) ; 
 struct msmsdcc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_resume_host (struct mmc_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
msmsdcc_resume(struct platform_device *dev)
{
	struct mmc_host *mmc = mmc_get_drvdata(dev);
	unsigned long flags;

	if (mmc) {
		struct msmsdcc_host *host = mmc_priv(mmc);

		spin_lock_irqsave(&host->lock, flags);

		if (!host->clks_on) {
			clk_enable(host->pclk);
			clk_enable(host->clk);
			host->clks_on = 1;
		}

		writel(host->saved_irq0mask, host->base + MMCIMASK0);

		spin_unlock_irqrestore(&host->lock, flags);

		if (mmc->card && mmc->card->type != MMC_TYPE_SDIO)
			mmc_resume_host(mmc);
			if (host->stat_irq)
				enable_irq(host->stat_irq);
		else if (host->stat_irq)
			enable_irq(host->stat_irq);
	}
	return 0;
}