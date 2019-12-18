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
struct mmc_host {TYPE_1__* bus_ops; scalar_t__ bus_dead; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* power_save ) (struct mmc_host*) ;int /*<<< orphan*/  power_restore; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_bus_get (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_bus_put (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_power_off (struct mmc_host*) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*) ; 

void mmc_power_save_host(struct mmc_host *host)
{
	mmc_bus_get(host);

	if (!host->bus_ops || host->bus_dead || !host->bus_ops->power_restore) {
		mmc_bus_put(host);
		return;
	}

	if (host->bus_ops->power_save)
		host->bus_ops->power_save(host);

	mmc_bus_put(host);

	mmc_power_off(host);
}