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
struct net_device {int dummy; } ;

/* Variables and functions */
 struct veth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static void veth_dellink(struct net_device *dev)
{
	struct veth_priv *priv;
	struct net_device *peer;

	priv = netdev_priv(dev);
	peer = priv->peer;

	unregister_netdevice(dev);
	unregister_netdevice(peer);
}