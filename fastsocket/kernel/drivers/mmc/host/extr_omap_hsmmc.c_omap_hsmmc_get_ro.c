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
struct omap_hsmmc_host {int /*<<< orphan*/  dev; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int (* get_ro ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOSYS ; 
 struct omap_hsmmc_host* mmc_priv (struct mmc_host*) ; 
 TYPE_1__ mmc_slot (struct omap_hsmmc_host*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hsmmc_get_ro(struct mmc_host *mmc)
{
	struct omap_hsmmc_host *host = mmc_priv(mmc);

	if (!mmc_slot(host).get_ro)
		return -ENOSYS;
	return mmc_slot(host).get_ro(host->dev, 0);
}