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
struct mmci_host {int gpio_wp; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int gpio_get_value (int) ; 
 struct mmci_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static int mmci_get_ro(struct mmc_host *mmc)
{
	struct mmci_host *host = mmc_priv(mmc);

	if (host->gpio_wp == -ENOSYS)
		return -ENOSYS;

	return gpio_get_value(host->gpio_wp);
}