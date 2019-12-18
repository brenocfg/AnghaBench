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
struct mmc_omap_host {int abort; int /*<<< orphan*/  slot_lock; int /*<<< orphan*/  cmd_abort_work; int /*<<< orphan*/  irq; int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IE ; 
 int /*<<< orphan*/  OMAP_MMC_WRITE (struct mmc_omap_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
mmc_omap_cmd_timer(unsigned long data)
{
	struct mmc_omap_host *host = (struct mmc_omap_host *) data;
	unsigned long flags;

	spin_lock_irqsave(&host->slot_lock, flags);
	if (host->cmd != NULL && !host->abort) {
		OMAP_MMC_WRITE(host, IE, 0);
		disable_irq(host->irq);
		host->abort = 1;
		schedule_work(&host->cmd_abort_work);
	}
	spin_unlock_irqrestore(&host->slot_lock, flags);
}