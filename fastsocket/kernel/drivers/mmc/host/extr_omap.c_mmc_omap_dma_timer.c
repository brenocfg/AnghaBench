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
struct mmc_omap_host {int dma_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  omap_free_dma (int) ; 

__attribute__((used)) static void
mmc_omap_dma_timer(unsigned long data)
{
	struct mmc_omap_host *host = (struct mmc_omap_host *) data;

	BUG_ON(host->dma_ch < 0);
	omap_free_dma(host->dma_ch);
	host->dma_ch = -1;
}