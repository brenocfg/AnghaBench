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
struct efx_nic {int /*<<< orphan*/  mac_work; int /*<<< orphan*/  monitor_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_selftest_async_cancel (struct efx_nic*) ; 

__attribute__((used)) static void efx_flush_all(struct efx_nic *efx)
{
	/* Make sure the hardware monitor and event self-test are stopped */
	cancel_delayed_work_sync(&efx->monitor_work);
	efx_selftest_async_cancel(efx);
	/* Stop scheduled port reconfigurations */
	cancel_work_sync(&efx->mac_work);
}