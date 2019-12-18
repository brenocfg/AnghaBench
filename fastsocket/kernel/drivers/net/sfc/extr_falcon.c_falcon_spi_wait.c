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
struct efx_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  falcon_spi_poll (struct efx_nic*) ; 
 int /*<<< orphan*/  hw ; 
 int jiffies ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_after_eq (int,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int falcon_spi_wait(struct efx_nic *efx)
{
	/* Most commands will finish quickly, so we start polling at
	 * very short intervals.  Sometimes the command may have to
	 * wait for VPD or expansion ROM access outside of our
	 * control, so we allow up to 100 ms. */
	unsigned long timeout = jiffies + 1 + DIV_ROUND_UP(HZ, 10);
	int i;

	for (i = 0; i < 10; i++) {
		if (!falcon_spi_poll(efx))
			return 0;
		udelay(10);
	}

	for (;;) {
		if (!falcon_spi_poll(efx))
			return 0;
		if (time_after_eq(jiffies, timeout)) {
			netif_err(efx, hw, efx->net_dev,
				  "timed out waiting for SPI\n");
			return -ETIMEDOUT;
		}
		schedule_timeout_uninterruptible(1);
	}
}