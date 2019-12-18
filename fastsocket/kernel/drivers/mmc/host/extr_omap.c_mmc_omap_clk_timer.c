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
struct mmc_omap_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_omap_fclk_enable (struct mmc_omap_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmc_omap_clk_timer(unsigned long data)
{
	struct mmc_omap_host *host = (struct mmc_omap_host *) data;

	mmc_omap_fclk_enable(host, 0);
}