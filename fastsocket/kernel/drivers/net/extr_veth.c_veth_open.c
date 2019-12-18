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
struct veth_priv {struct net_device* peer; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int IFF_UP ; 
 struct veth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

__attribute__((used)) static int veth_open(struct net_device *dev)
{
	struct veth_priv *priv;

	priv = netdev_priv(dev);
	if (priv->peer == NULL)
		return -ENOTCONN;

	if (priv->peer->flags & IFF_UP) {
		netif_carrier_on(dev);
		netif_carrier_on(priv->peer);
	}
	return 0;
}