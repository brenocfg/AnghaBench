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
struct mmc_host {int /*<<< orphan*/  sdio_irqs; int /*<<< orphan*/  sdio_irq_thread; int /*<<< orphan*/  sdio_irq_thread_abort; int /*<<< orphan*/  claimed; } ;
struct mmc_card {struct mmc_host* host; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct mmc_host*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  sdio_irq_thread ; 

__attribute__((used)) static int sdio_card_irq_get(struct mmc_card *card)
{
	struct mmc_host *host = card->host;

	WARN_ON(!host->claimed);

	if (!host->sdio_irqs++) {
		atomic_set(&host->sdio_irq_thread_abort, 0);
		host->sdio_irq_thread =
			kthread_run(sdio_irq_thread, host, "ksdioirqd/%s",
				mmc_hostname(host));
		if (IS_ERR(host->sdio_irq_thread)) {
			int err = PTR_ERR(host->sdio_irq_thread);
			host->sdio_irqs--;
			return err;
		}
	}

	return 0;
}