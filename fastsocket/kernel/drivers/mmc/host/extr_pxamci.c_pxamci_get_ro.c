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
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_ro ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  gpio_card_ro; scalar_t__ gpio_card_ro_invert; } ;

/* Variables and functions */
 int ENOSYS ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 struct pxamci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxamci_get_ro(struct mmc_host *mmc)
{
	struct pxamci_host *host = mmc_priv(mmc);

	if (host->pdata && gpio_is_valid(host->pdata->gpio_card_ro)) {
		if (host->pdata->gpio_card_ro_invert)
			return !gpio_get_value(host->pdata->gpio_card_ro);
		else
			return gpio_get_value(host->pdata->gpio_card_ro);
	}
	if (host->pdata && host->pdata->get_ro)
		return !!host->pdata->get_ro(mmc_dev(mmc));
	/*
	 * Board doesn't support read only detection; let the mmc core
	 * decide what to do.
	 */
	return -ENOSYS;
}