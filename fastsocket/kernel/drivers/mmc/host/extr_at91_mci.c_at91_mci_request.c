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
struct mmc_request {int dummy; } ;
struct mmc_host {int dummy; } ;
struct at91mci_host {int /*<<< orphan*/  timer; scalar_t__ flags; struct mmc_request* request; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  at91_mci_process_next (struct at91mci_host*) ; 
 scalar_t__ jiffies ; 
 struct at91mci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void at91_mci_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct at91mci_host *host = mmc_priv(mmc);
	host->request = mrq;
	host->flags = 0;

	mod_timer(&host->timer, jiffies +  HZ);

	at91_mci_process_next(host);
}