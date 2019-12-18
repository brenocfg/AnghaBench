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
struct net_device {int flags; int /*<<< orphan*/  dev; scalar_t__ mc_count; } ;
struct enc28j60_net {int rxfilter; int /*<<< orphan*/  setrx_work; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int RXFILTER_MULTI ; 
 int RXFILTER_NORMAL ; 
 int RXFILTER_PROMISC ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 struct enc28j60_net* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_link (struct enc28j60_net*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enc28j60_set_multicast_list(struct net_device *dev)
{
	struct enc28j60_net *priv = netdev_priv(dev);
	int oldfilter = priv->rxfilter;

	if (dev->flags & IFF_PROMISC) {
		if (netif_msg_link(priv))
			dev_info(&dev->dev, "promiscuous mode\n");
		priv->rxfilter = RXFILTER_PROMISC;
	} else if ((dev->flags & IFF_ALLMULTI) || dev->mc_count) {
		if (netif_msg_link(priv))
			dev_info(&dev->dev, "%smulticast mode\n",
				(dev->flags & IFF_ALLMULTI) ? "all-" : "");
		priv->rxfilter = RXFILTER_MULTI;
	} else {
		if (netif_msg_link(priv))
			dev_info(&dev->dev, "normal mode\n");
		priv->rxfilter = RXFILTER_NORMAL;
	}

	if (oldfilter != priv->rxfilter)
		schedule_work(&priv->setrx_work);
}