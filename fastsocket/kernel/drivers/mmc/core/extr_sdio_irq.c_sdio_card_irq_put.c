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
struct mmc_host {int sdio_irqs; int /*<<< orphan*/  sdio_irq_thread; int /*<<< orphan*/  sdio_irq_thread_abort; int /*<<< orphan*/  claimed; } ;
struct mmc_card {struct mmc_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdio_card_irq_put(struct mmc_card *card)
{
	struct mmc_host *host = card->host;

	WARN_ON(!host->claimed);
	BUG_ON(host->sdio_irqs < 1);

	if (!--host->sdio_irqs) {
		atomic_set(&host->sdio_irq_thread_abort, 1);
		kthread_stop(host->sdio_irq_thread);
	}

	return 0;
}