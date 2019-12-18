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
typedef  int u16 ;
struct sdhci_host {scalar_t__ version; int /*<<< orphan*/  lock; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int SDHCI_CTRL_PRESET_VAL_ENABLE ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 scalar_t__ SDHCI_SPEC_300 ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sdhci_enable_preset_value(struct mmc_host *mmc, bool enable)
{
	struct sdhci_host *host;
	u16 ctrl;
	unsigned long flags;

	host = mmc_priv(mmc);

	/* Host Controller v3.00 defines preset value registers */
	if (host->version < SDHCI_SPEC_300)
		return;

	spin_lock_irqsave(&host->lock, flags);

	ctrl = sdhci_readw(host, SDHCI_HOST_CONTROL2);

	/*
	 * We only enable or disable Preset Value if they are not already
	 * enabled or disabled respectively. Otherwise, we bail out.
	 */
	if (enable && !(ctrl & SDHCI_CTRL_PRESET_VAL_ENABLE)) {
		ctrl |= SDHCI_CTRL_PRESET_VAL_ENABLE;
		sdhci_writew(host, ctrl, SDHCI_HOST_CONTROL2);
	} else if (!enable && (ctrl & SDHCI_CTRL_PRESET_VAL_ENABLE)) {
		ctrl &= ~SDHCI_CTRL_PRESET_VAL_ENABLE;
		sdhci_writew(host, ctrl, SDHCI_HOST_CONTROL2);
	}

	spin_unlock_irqrestore(&host->lock, flags);
}