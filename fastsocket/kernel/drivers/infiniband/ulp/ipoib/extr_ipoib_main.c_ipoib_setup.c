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
struct net_device {int flags; int tx_queue_len; int features; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  type; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  neigh_reap_task; int /*<<< orphan*/  ah_reap_task; int /*<<< orphan*/  restart_task; int /*<<< orphan*/  flush_heavy; int /*<<< orphan*/  flush_normal; int /*<<< orphan*/  flush_light; int /*<<< orphan*/  carrier_on_task; int /*<<< orphan*/  mcast_task; int /*<<< orphan*/  pkey_poll_task; int /*<<< orphan*/  multicast_list; int /*<<< orphan*/  dead_ahs; int /*<<< orphan*/  child_intfs; int /*<<< orphan*/  path_list; int /*<<< orphan*/  vlan_mutex; int /*<<< orphan*/  lock; struct net_device* dev; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_INFINIBAND ; 
 int /*<<< orphan*/  HZ ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  IFF_XMIT_DST_RELEASE ; 
 int /*<<< orphan*/  INFINIBAND_ALEN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPOIB_ENCAP_LEN ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  ipoib_header_ops ; 
 int /*<<< orphan*/  ipoib_ib_dev_flush_heavy ; 
 int /*<<< orphan*/  ipoib_ib_dev_flush_light ; 
 int /*<<< orphan*/  ipoib_ib_dev_flush_normal ; 
 int /*<<< orphan*/  ipoib_mcast_carrier_on_task ; 
 int /*<<< orphan*/  ipoib_mcast_join_task ; 
 int /*<<< orphan*/  ipoib_mcast_restart_task ; 
 int /*<<< orphan*/  ipoib_netdev_ops ; 
 int /*<<< orphan*/  ipoib_pkey_poll ; 
 int /*<<< orphan*/  ipoib_poll ; 
 int /*<<< orphan*/  ipoib_reap_ah ; 
 int /*<<< orphan*/  ipoib_reap_neigh ; 
 int ipoib_sendq_size ; 
 int /*<<< orphan*/  ipoib_set_ethtool_ops (struct net_device*) ; 
 int /*<<< orphan*/  ipv4_bcast_addr ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void ipoib_setup(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);

	dev->netdev_ops		 = &ipoib_netdev_ops;
	dev->header_ops		 = &ipoib_header_ops;

	ipoib_set_ethtool_ops(dev);

	netif_napi_add(dev, &priv->napi, ipoib_poll, 100);

	dev->watchdog_timeo	 = HZ;

	dev->flags		|= IFF_BROADCAST | IFF_MULTICAST;

	dev->hard_header_len	 = IPOIB_ENCAP_LEN;
	dev->addr_len		 = INFINIBAND_ALEN;
	dev->type		 = ARPHRD_INFINIBAND;
	dev->tx_queue_len	 = ipoib_sendq_size * 2;
	dev->features		 = (NETIF_F_VLAN_CHALLENGED	|
				    NETIF_F_HIGHDMA);
	dev->priv_flags		&= ~IFF_XMIT_DST_RELEASE;

	memcpy(dev->broadcast, ipv4_bcast_addr, INFINIBAND_ALEN);

	priv->dev = dev;

	spin_lock_init(&priv->lock);

	mutex_init(&priv->vlan_mutex);

	INIT_LIST_HEAD(&priv->path_list);
	INIT_LIST_HEAD(&priv->child_intfs);
	INIT_LIST_HEAD(&priv->dead_ahs);
	INIT_LIST_HEAD(&priv->multicast_list);

	INIT_DELAYED_WORK(&priv->pkey_poll_task, ipoib_pkey_poll);
	INIT_DELAYED_WORK(&priv->mcast_task,   ipoib_mcast_join_task);
	INIT_WORK(&priv->carrier_on_task, ipoib_mcast_carrier_on_task);
	INIT_WORK(&priv->flush_light,   ipoib_ib_dev_flush_light);
	INIT_WORK(&priv->flush_normal,   ipoib_ib_dev_flush_normal);
	INIT_WORK(&priv->flush_heavy,   ipoib_ib_dev_flush_heavy);
	INIT_WORK(&priv->restart_task, ipoib_mcast_restart_task);
	INIT_DELAYED_WORK(&priv->ah_reap_task, ipoib_reap_ah);
	INIT_DELAYED_WORK(&priv->neigh_reap_task, ipoib_reap_neigh);
}