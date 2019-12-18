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
struct net_device {int addr_len; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  type; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  dev_addr; } ;
struct iphdr {scalar_t__ saddr; scalar_t__ daddr; } ;
struct TYPE_2__ {struct iphdr iph; } ;
struct ip_tunnel {TYPE_1__ parms; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IPGRE ; 
 int EINVAL ; 
 int /*<<< orphan*/  IFF_BROADCAST ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  IFF_XMIT_DST_RELEASE ; 
 int /*<<< orphan*/  __gre_tunnel_init (struct net_device*) ; 
 int ip_tunnel_init (struct net_device*) ; 
 int /*<<< orphan*/  ipgre_header_ops ; 
 scalar_t__ ipv4_is_multicast (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ipgre_tunnel_init(struct net_device *dev)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	struct iphdr *iph = &tunnel->parms.iph;

	__gre_tunnel_init(dev);

	memcpy(dev->dev_addr, &iph->saddr, 4);
	memcpy(dev->broadcast, &iph->daddr, 4);

	dev->type		= ARPHRD_IPGRE;
	dev->flags		= IFF_NOARP;
	dev->priv_flags		&= ~IFF_XMIT_DST_RELEASE;
	dev->addr_len		= 4;

	if (iph->daddr) {
#ifdef CONFIG_NET_IPGRE_BROADCAST
		if (ipv4_is_multicast(iph->daddr)) {
			if (!iph->saddr)
				return -EINVAL;
			dev->flags = IFF_BROADCAST;
			dev->header_ops = &ipgre_header_ops;
		}
#endif
	} else
		dev->header_ops = &ipgre_header_ops;

	return ip_tunnel_init(dev);
}