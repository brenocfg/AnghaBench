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
struct omap_hsmmc_host {int /*<<< orphan*/  mmc_carddetect_work; scalar_t__ suspended; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t omap_hsmmc_cd_handler(int irq, void *dev_id)
{
	struct omap_hsmmc_host *host = (struct omap_hsmmc_host *)dev_id;

	if (host->suspended)
		return IRQ_HANDLED;
	schedule_work(&host->mmc_carddetect_work);

	return IRQ_HANDLED;
}