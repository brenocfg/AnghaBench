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
struct net_device {int mtu; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; int /*<<< orphan*/  mac_lock; TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reconfigure_mac ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int EFX_MAX_MTU ; 
 int EINVAL ; 
 int /*<<< orphan*/  drv ; 
 int efx_check_disabled (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_device_detach_sync (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_start_all (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_stop_all (struct efx_nic*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_device_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 

__attribute__((used)) static int efx_change_mtu(struct net_device *net_dev, int new_mtu)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	int rc;

	rc = efx_check_disabled(efx);
	if (rc)
		return rc;
	if (new_mtu > EFX_MAX_MTU)
		return -EINVAL;

	netif_dbg(efx, drv, efx->net_dev, "changing MTU to %d\n", new_mtu);

	efx_device_detach_sync(efx);
	efx_stop_all(efx);

	mutex_lock(&efx->mac_lock);
	net_dev->mtu = new_mtu;
	efx->type->reconfigure_mac(efx);
	mutex_unlock(&efx->mac_lock);

	efx_start_all(efx);
	netif_device_attach(efx->net_dev);
	return 0;
}