#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  mtu; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/  type; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * wireless_handlers; TYPE_1__* wireless_data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * spy_data; } ;
struct hostap_interface {TYPE_1__ wireless_data; int /*<<< orphan*/  spy_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  mtu; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_7__ {int /*<<< orphan*/  ext_priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE80211 ; 
#define  HOSTAP_INTERFACE_AP 129 
#define  HOSTAP_INTERFACE_MASTER 128 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  hostap_80211_ops ; 
 int /*<<< orphan*/  hostap_iw_handler_def ; 
 int /*<<< orphan*/  hostap_master_ops ; 
 int /*<<< orphan*/  hostap_mgmt_netdev_ops ; 
 int /*<<< orphan*/  hostap_netdev_ops ; 
 TYPE_3__* netdev_extended (struct net_device*) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  prism2_ethtool_ops ; 

void hostap_setup_dev(struct net_device *dev, local_info_t *local,
		      int type)
{
	struct hostap_interface *iface;

	iface = netdev_priv(dev);
	ether_setup(dev);
	netdev_extended(dev)->ext_priv_flags &= ~IFF_TX_SKB_SHARING;

	/* kernel callbacks */
	if (iface) {
		/* Currently, we point to the proper spy_data only on
		 * the main_dev. This could be fixed. Jean II */
		iface->wireless_data.spy_data = &iface->spy_data;
		dev->wireless_data = &iface->wireless_data;
	}
	dev->wireless_handlers = &hostap_iw_handler_def;
	dev->watchdog_timeo = TX_TIMEOUT;

	switch(type) {
	case HOSTAP_INTERFACE_AP:
		dev->tx_queue_len = 0;	/* use main radio device queue */
		dev->netdev_ops = &hostap_mgmt_netdev_ops;
		dev->type = ARPHRD_IEEE80211;
		dev->header_ops = &hostap_80211_ops;
		break;
	case HOSTAP_INTERFACE_MASTER:
		dev->netdev_ops = &hostap_master_ops;
		break;
	default:
		dev->tx_queue_len = 0;	/* use main radio device queue */
		dev->netdev_ops = &hostap_netdev_ops;
	}

	dev->mtu = local->mtu;


	SET_ETHTOOL_OPS(dev, &prism2_ethtool_ops);

}