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
struct mmc_host {int /*<<< orphan*/  claimed; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mmc_do_release_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_host_lazy_disable (struct mmc_host*) ; 

void mmc_release_host(struct mmc_host *host)
{
	WARN_ON(!host->claimed);

	mmc_host_lazy_disable(host);

	mmc_do_release_host(host);
}