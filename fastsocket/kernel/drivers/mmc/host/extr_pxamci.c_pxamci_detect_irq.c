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
struct pxamci_host {TYPE_1__* pdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  detect_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mmc_detect_change (void*,int /*<<< orphan*/ ) ; 
 struct pxamci_host* mmc_priv (void*) ; 

__attribute__((used)) static irqreturn_t pxamci_detect_irq(int irq, void *devid)
{
	struct pxamci_host *host = mmc_priv(devid);

	mmc_detect_change(devid, host->pdata->detect_delay);
	return IRQ_HANDLED;
}