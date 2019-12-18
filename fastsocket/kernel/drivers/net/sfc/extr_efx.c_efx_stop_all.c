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
struct efx_nic {int /*<<< orphan*/  net_dev; TYPE_1__* type; int /*<<< orphan*/  port_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop_stats ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_ASSERT_RESET_SERIALISED (struct efx_nic*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  efx_flush_all (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_stop_datapath (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_stop_port (struct efx_nic*) ; 
 scalar_t__ netif_device_present (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 

__attribute__((used)) static void efx_stop_all(struct efx_nic *efx)
{
	EFX_ASSERT_RESET_SERIALISED(efx);

	/* port_enabled can be read safely under the rtnl lock */
	if (!efx->port_enabled)
		return;

	efx->type->stop_stats(efx);
	efx_stop_port(efx);

	/* Flush efx_mac_work(), refill_workqueue, monitor_work */
	efx_flush_all(efx);

	/* Stop the kernel transmit interface.  This is only valid if
	 * the device is stopped or detached; otherwise the watchdog
	 * may fire immediately.
	 */
	WARN_ON(netif_running(efx->net_dev) &&
		netif_device_present(efx->net_dev));
	netif_tx_disable(efx->net_dev);

	efx_stop_datapath(efx);
}