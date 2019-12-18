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
struct mmc_spi_host {TYPE_1__* pdata; } ;
struct mmc_host {int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_cd ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 struct mmc_spi_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_spi_get_cd(struct mmc_host *mmc)
{
	struct mmc_spi_host *host = mmc_priv(mmc);

	if (host->pdata && host->pdata->get_cd)
		return !!host->pdata->get_cd(mmc->parent);
	return -ENOSYS;
}