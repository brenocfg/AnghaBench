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
struct mmci_host {int /*<<< orphan*/  gpio_cd; int /*<<< orphan*/  mmc; TYPE_1__* plat; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {unsigned int (* status ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 unsigned int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 struct mmci_host* mmc_priv (struct mmc_host*) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmci_get_cd(struct mmc_host *mmc)
{
	struct mmci_host *host = mmc_priv(mmc);
	unsigned int status;

	if (host->gpio_cd == -ENOSYS)
		status = host->plat->status(mmc_dev(host->mmc));
	else
		status = gpio_get_value(host->gpio_cd);

	return !status;
}