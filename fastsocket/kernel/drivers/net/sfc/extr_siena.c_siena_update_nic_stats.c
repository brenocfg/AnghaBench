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
struct efx_nic {int dummy; } ;

/* Variables and functions */
 scalar_t__ siena_try_update_nic_stats (struct efx_nic*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void siena_update_nic_stats(struct efx_nic *efx)
{
	int retry;

	/* If we're unlucky enough to read statistics wduring the DMA, wait
	 * up to 10ms for it to finish (typically takes <500us) */
	for (retry = 0; retry < 100; ++retry) {
		if (siena_try_update_nic_stats(efx) == 0)
			return;
		udelay(100);
	}

	/* Use the old values instead */
}