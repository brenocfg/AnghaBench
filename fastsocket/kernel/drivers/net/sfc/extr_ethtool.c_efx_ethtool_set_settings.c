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
struct net_device {int dummy; } ;
struct ethtool_cmd {scalar_t__ duplex; } ;
struct efx_nic {int /*<<< orphan*/  mac_lock; TYPE_1__* phy_op; int /*<<< orphan*/  net_dev; } ;
struct TYPE_2__ {int (* set_settings ) (struct efx_nic*,struct ethtool_cmd*) ;} ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  drv ; 
 scalar_t__ ethtool_cmd_speed (struct ethtool_cmd*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct efx_nic*,struct ethtool_cmd*) ; 

__attribute__((used)) static int efx_ethtool_set_settings(struct net_device *net_dev,
				    struct ethtool_cmd *ecmd)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	int rc;

	/* GMAC does not support 1000Mbps HD */
	if ((ethtool_cmd_speed(ecmd) == SPEED_1000) &&
	    (ecmd->duplex != DUPLEX_FULL)) {
		netif_dbg(efx, drv, efx->net_dev,
			  "rejecting unsupported 1000Mbps HD setting\n");
		return -EINVAL;
	}

	mutex_lock(&efx->mac_lock);
	rc = efx->phy_op->set_settings(efx, ecmd);
	mutex_unlock(&efx->mac_lock);
	return rc;
}