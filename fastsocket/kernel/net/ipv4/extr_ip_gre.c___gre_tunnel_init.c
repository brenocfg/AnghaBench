#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int mtu; int features; scalar_t__ needed_headroom; } ;
struct iphdr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int o_flags; TYPE_1__ iph; } ;
struct ip_tunnel {TYPE_2__ parms; int /*<<< orphan*/  hlen; } ;

/* Variables and functions */
 int ETH_DATA_LEN ; 
 int GRE_FEATURES ; 
 int /*<<< orphan*/  IPPROTO_GRE ; 
 scalar_t__ LL_MAX_HEADER ; 
 int NETIF_F_GSO_SOFTWARE ; 
 int NETIF_F_LLTX ; 
 int NETIF_F_NETNS_LOCAL ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int TUNNEL_SEQ ; 
 int /*<<< orphan*/  gre_dev_ethtool_ops ; 
 int /*<<< orphan*/  ip_gre_calc_hlen (int) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void __gre_tunnel_init(struct net_device *dev)
{
	struct ip_tunnel *tunnel;

	tunnel = netdev_priv(dev);
	tunnel->hlen = ip_gre_calc_hlen(tunnel->parms.o_flags);
	tunnel->parms.iph.protocol = IPPROTO_GRE;

	dev->needed_headroom	= LL_MAX_HEADER + sizeof(struct iphdr) + 4;
	dev->mtu		= ETH_DATA_LEN - sizeof(struct iphdr) - 4;

	dev->features		|= NETIF_F_NETNS_LOCAL | GRE_FEATURES;

	if (!(tunnel->parms.o_flags & TUNNEL_SEQ)) {
		/* TCP offload with GRE SEQ is not supported. */
		dev->features    |= NETIF_F_GSO_SOFTWARE;
		/* Can use a lockless transmit, unless we generate
		 * output sequences
		 */
		dev->features |= NETIF_F_LLTX;
	}
	SET_ETHTOOL_OPS(dev, &gre_dev_ethtool_ops);
}