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
struct mmc_host {int dummy; } ;
struct at91mci_host {TYPE_1__* board; int /*<<< orphan*/  mmc; } ;
struct TYPE_2__ {scalar_t__ slot_b; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_MCI_IDR ; 
 int /*<<< orphan*/  AT91_MCI_IER ; 
 int /*<<< orphan*/  AT91_MCI_SDIOIRQA ; 
 int /*<<< orphan*/  AT91_MCI_SDIOIRQB ; 
 int /*<<< orphan*/  at91_mci_write (struct at91mci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 struct at91mci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char,char*) ; 

__attribute__((used)) static void at91_mci_enable_sdio_irq(struct mmc_host *mmc, int enable)
{
	struct at91mci_host *host = mmc_priv(mmc);

	pr_debug("%s: sdio_irq %c : %s\n", mmc_hostname(host->mmc),
		host->board->slot_b ? 'B':'A', enable ? "enable" : "disable");
	at91_mci_write(host, enable ? AT91_MCI_IER : AT91_MCI_IDR,
		host->board->slot_b ? AT91_MCI_SDIOIRQB : AT91_MCI_SDIOIRQA);

}