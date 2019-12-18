#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct net_device* dev; } ;
struct TYPE_5__ {TYPE_1__ dst; } ;
struct rtable {TYPE_2__ u; } ;
struct net_device {scalar_t__ type; int hard_header_len; int needed_headroom; int mtu; scalar_t__ iflink; int /*<<< orphan*/  flags; } ;
struct iphdr {int /*<<< orphan*/  tos; int /*<<< orphan*/  saddr; scalar_t__ daddr; int /*<<< orphan*/  protocol; } ;
struct TYPE_6__ {scalar_t__ link; int /*<<< orphan*/  o_key; struct iphdr iph; } ;
struct ip_tunnel {int hlen; TYPE_3__ parms; } ;
struct flowi {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int ETH_DATA_LEN ; 
 int /*<<< orphan*/  IFF_POINTOPOINT ; 
 int /*<<< orphan*/  IS_ERR (struct rtable*) ; 
 int LL_MAX_HEADER ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct rtable* ip_route_output_tunnel (int /*<<< orphan*/ ,struct flowi*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 struct ip_tunnel* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ip_tunnel_bind_dev(struct net_device *dev)
{
	struct net_device *tdev = NULL;
	struct ip_tunnel *tunnel = netdev_priv(dev);
	const struct iphdr *iph;
	int hlen = LL_MAX_HEADER;
	int mtu = ETH_DATA_LEN;
	int t_hlen = tunnel->hlen + sizeof(struct iphdr);

	iph = &tunnel->parms.iph;

	/* Guess output device to choose reasonable mtu and needed_headroom */
	if (iph->daddr) {
		struct flowi fl4;
		struct rtable *rt;

		rt = ip_route_output_tunnel(dev_net(dev), &fl4,
					    tunnel->parms.iph.protocol,
					    iph->daddr, iph->saddr,
					    tunnel->parms.o_key,
					    RT_TOS(iph->tos),
					    tunnel->parms.link);
		if (!IS_ERR(rt)) {
			tdev = rt->u.dst.dev;
			ip_rt_put(rt);
		}
		if (dev->type != ARPHRD_ETHER)
			dev->flags |= IFF_POINTOPOINT;
	}

	if (!tdev && tunnel->parms.link)
		tdev = __dev_get_by_index(dev_net(dev), tunnel->parms.link);

	if (tdev) {
		hlen = tdev->hard_header_len + tdev->needed_headroom;
		mtu = tdev->mtu;
	}
	dev->iflink = tunnel->parms.link;

	dev->needed_headroom = t_hlen + hlen;
	mtu -= (dev->hard_header_len + t_hlen);

	if (mtu < 68)
		mtu = 68;

	return mtu;
}