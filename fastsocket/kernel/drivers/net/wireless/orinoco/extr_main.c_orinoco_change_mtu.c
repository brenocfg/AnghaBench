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
struct orinoco_private {scalar_t__ nicbuf_size; } ;
struct net_device {int mtu; } ;
struct ieee80211_hdr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ENCAPS_OVERHEAD ; 
 scalar_t__ ETH_HLEN ; 
 int ORINOCO_MAX_MTU ; 
 int ORINOCO_MIN_MTU ; 
 struct orinoco_private* ndev_priv (struct net_device*) ; 

int orinoco_change_mtu(struct net_device *dev, int new_mtu)
{
	struct orinoco_private *priv = ndev_priv(dev);

	if ((new_mtu < ORINOCO_MIN_MTU) || (new_mtu > ORINOCO_MAX_MTU))
		return -EINVAL;

	/* MTU + encapsulation + header length */
	if ((new_mtu + ENCAPS_OVERHEAD + sizeof(struct ieee80211_hdr)) >
	     (priv->nicbuf_size - ETH_HLEN))
		return -EINVAL;

	dev->mtu = new_mtu;

	return 0;
}