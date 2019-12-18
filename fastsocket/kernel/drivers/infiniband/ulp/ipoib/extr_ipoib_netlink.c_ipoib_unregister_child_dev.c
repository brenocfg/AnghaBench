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
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  vlan_mutex; int /*<<< orphan*/  list; struct net_device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice_queue (struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoib_unregister_child_dev(struct net_device *dev)
{
	struct ipoib_dev_priv *priv, *ppriv;

	priv = netdev_priv(dev);
	ppriv = netdev_priv(priv->parent);

	mutex_lock(&ppriv->vlan_mutex);
	unregister_netdevice_queue(dev, NULL);
	list_del(&priv->list);
	mutex_unlock(&ppriv->vlan_mutex);
}