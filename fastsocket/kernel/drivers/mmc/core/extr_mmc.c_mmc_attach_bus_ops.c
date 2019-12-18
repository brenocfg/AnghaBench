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
struct mmc_host {int caps; } ;
struct mmc_bus_ops {int dummy; } ;

/* Variables and functions */
 int MMC_CAP_NONREMOVABLE ; 
 int /*<<< orphan*/  mmc_attach_bus (struct mmc_host*,struct mmc_bus_ops const*) ; 
 struct mmc_bus_ops mmc_ops ; 
 struct mmc_bus_ops mmc_ops_unsafe ; 

__attribute__((used)) static void mmc_attach_bus_ops(struct mmc_host *host)
{
	const struct mmc_bus_ops *bus_ops;

	if (host->caps & MMC_CAP_NONREMOVABLE)
		bus_ops = &mmc_ops_unsafe;
	else
		bus_ops = &mmc_ops;
	mmc_attach_bus(host, bus_ops);
}