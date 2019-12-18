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
typedef  int u32 ;
struct sdhci_host {int quirks; int flags; int /*<<< orphan*/  lock; struct mmc_request* mrq; int /*<<< orphan*/  finish_tasklet; } ;
struct mmc_request {TYPE_1__* cmd; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEDIUM ; 
 int SDHCI_CARD_PRESENT ; 
 int SDHCI_DEVICE_DEAD ; 
 int SDHCI_DOING_READ ; 
 int SDHCI_DOING_WRITE ; 
 int SDHCI_NEEDS_RETUNING ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int SDHCI_QUIRK_BROKEN_CARD_DETECTION ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  sdhci_activate_led (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_execute_tuning (struct mmc_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_send_command (struct sdhci_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdhci_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct sdhci_host *host;
	bool present;
	unsigned long flags;

	host = mmc_priv(mmc);

	spin_lock_irqsave(&host->lock, flags);

	WARN_ON(host->mrq != NULL);

#ifndef SDHCI_USE_LEDS_CLASS
	sdhci_activate_led(host);
#endif

	host->mrq = mrq;

	/* If polling, assume that the card is always present. */
	if (host->quirks & SDHCI_QUIRK_BROKEN_CARD_DETECTION)
		present = true;
	else
		present = sdhci_readl(host, SDHCI_PRESENT_STATE) &
				SDHCI_CARD_PRESENT;

	if (!present || host->flags & SDHCI_DEVICE_DEAD) {
		host->mrq->cmd->error = -ENOMEDIUM;
		tasklet_schedule(&host->finish_tasklet);
	} else {
		u32 present_state;

		present_state = sdhci_readl(host, SDHCI_PRESENT_STATE);
		/*
		 * Check if the re-tuning timer has already expired and there
		 * is no on-going data transfer. If so, we need to execute
		 * tuning procedure before sending command.
		 */
		if ((host->flags & SDHCI_NEEDS_RETUNING) &&
		    !(present_state & (SDHCI_DOING_WRITE | SDHCI_DOING_READ))) {
			spin_unlock_irqrestore(&host->lock, flags);
			sdhci_execute_tuning(mmc);
			spin_lock_irqsave(&host->lock, flags);

			/* Restore original mmc_request structure */
			host->mrq = mrq;
		}

		sdhci_send_command(host, mrq->cmd);
	}

	mmiowb();
	spin_unlock_irqrestore(&host->lock, flags);
}