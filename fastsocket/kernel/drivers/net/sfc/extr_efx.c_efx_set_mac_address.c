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
struct sockaddr {char* sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct efx_nic {int /*<<< orphan*/  mac_lock; TYPE_1__* type; int /*<<< orphan*/  net_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reconfigure_mac ) (struct efx_nic*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_sriov_mac_address_changed (struct efx_nic*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*) ; 

__attribute__((used)) static int efx_set_mac_address(struct net_device *net_dev, void *data)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	struct sockaddr *addr = data;
	char *new_addr = addr->sa_data;

	if (!is_valid_ether_addr(new_addr)) {
		netif_err(efx, drv, efx->net_dev,
			  "invalid ethernet MAC address requested: %pM\n",
			  new_addr);
		return -EINVAL;
	}

	memcpy(net_dev->dev_addr, new_addr, net_dev->addr_len);
	efx_sriov_mac_address_changed(efx);

	/* Reconfigure the MAC */
	mutex_lock(&efx->mac_lock);
	efx->type->reconfigure_mac(efx);
	mutex_unlock(&efx->mac_lock);

	return 0;
}