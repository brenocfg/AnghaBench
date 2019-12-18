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
struct at91mci_host {int present; int /*<<< orphan*/  mmc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int AT91_MCI_SDCBUS ; 
 int /*<<< orphan*/  AT91_MCI_SDCR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int at91_mci_read (struct at91mci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_mci_write (struct at91mci_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_to_gpio (int) ; 
 int /*<<< orphan*/  mmc_detect_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static irqreturn_t at91_mmc_det_irq(int irq, void *_host)
{
	struct at91mci_host *host = _host;
	int present = !gpio_get_value(irq_to_gpio(irq));

	/*
	 * we expect this irq on both insert and remove,
	 * and use a short delay to debounce.
	 */
	if (present != host->present) {
		host->present = present;
		pr_debug("%s: card %s\n", mmc_hostname(host->mmc),
			present ? "insert" : "remove");
		if (!present) {
			pr_debug("****** Resetting SD-card bus width ******\n");
			at91_mci_write(host, AT91_MCI_SDCR, at91_mci_read(host, AT91_MCI_SDCR) & ~AT91_MCI_SDCBUS);
		}
		mmc_detect_change(host->mmc, msecs_to_jiffies(100));
	}
	return IRQ_HANDLED;
}