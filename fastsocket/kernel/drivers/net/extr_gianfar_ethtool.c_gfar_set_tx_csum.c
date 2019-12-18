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
typedef  scalar_t__ uint32_t ;
struct net_device {int /*<<< orphan*/  features; } ;
struct gfar_private {int device_flags; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int FSL_GIANFAR_DEV_HAS_CSUM ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (struct net_device*) ; 

__attribute__((used)) static int gfar_set_tx_csum(struct net_device *dev, uint32_t data)
{
	struct gfar_private *priv = netdev_priv(dev);

	if (!(priv->device_flags & FSL_GIANFAR_DEV_HAS_CSUM))
		return -EOPNOTSUPP;

	netif_tx_lock_bh(dev);

	if (data)
		dev->features |= NETIF_F_IP_CSUM;
	else
		dev->features &= ~NETIF_F_IP_CSUM;

	netif_tx_unlock_bh(dev);

	return 0;
}