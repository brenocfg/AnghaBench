#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vxlan_port {TYPE_3__* vs; } ;
struct vport {int /*<<< orphan*/  dp; } ;
struct sk_buff {int local_df; int /*<<< orphan*/  mark; } ;
struct rtable {int dummy; } ;
struct net {int dummy; } ;
struct flowi {int /*<<< orphan*/  fl4_src; int /*<<< orphan*/  proto; int /*<<< orphan*/  mark; int /*<<< orphan*/  fl4_tos; int /*<<< orphan*/  fl4_dst; } ;
typedef  int /*<<< orphan*/  fl ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_10__ {TYPE_2__* tun_key; } ;
struct TYPE_9__ {int /*<<< orphan*/  sport; } ;
struct TYPE_8__ {TYPE_1__* sock; } ;
struct TYPE_7__ {int tun_flags; int /*<<< orphan*/  tun_id; int /*<<< orphan*/  ipv4_ttl; int /*<<< orphan*/  ipv4_tos; int /*<<< orphan*/  ipv4_dst; int /*<<< orphan*/  ipv4_src; } ;
struct TYPE_6__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IP_DF ; 
 TYPE_5__* OVS_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 int TUNNEL_DONT_FRAGMENT ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_get_local_port_range (int*,int*) ; 
 TYPE_4__* inet_sk (int /*<<< orphan*/ ) ; 
 int ip_route_output_key (struct net*,struct rtable**,struct flowi*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 struct net* ovs_dp_get_net (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vxlan_src_port (int,int,struct sk_buff*) ; 
 struct vxlan_port* vxlan_vport (struct vport*) ; 
 int vxlan_xmit_skb (struct net*,TYPE_3__*,struct rtable*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxlan_tnl_send(struct vport *vport, struct sk_buff *skb)
{
	struct net *net = ovs_dp_get_net(vport->dp);
	struct vxlan_port *vxlan_port = vxlan_vport(vport);
	__be16 dst_port = inet_sk(vxlan_port->vs->sock->sk)->sport;
	struct rtable *rt;
	struct flowi fl;
	__be16 src_port;
	int port_min;
	int port_max;
	__be16 df;
	int err;

	if (unlikely(!OVS_CB(skb)->tun_key)) {
		err = -EINVAL;
		goto error;
	}

	/* Route lookup */
	memset(&fl, 0, sizeof(fl));
	fl.fl4_dst = OVS_CB(skb)->tun_key->ipv4_dst;
	fl.fl4_src = OVS_CB(skb)->tun_key->ipv4_src;
	fl.fl4_tos = RT_TOS(OVS_CB(skb)->tun_key->ipv4_tos);
	fl.mark = skb->mark;
	fl.proto = IPPROTO_UDP;

	err = ip_route_output_key(net, &rt, &fl);
	if (err)
		goto error;

	df = OVS_CB(skb)->tun_key->tun_flags & TUNNEL_DONT_FRAGMENT ?
		htons(IP_DF) : 0;

	skb->local_df = 1;

	inet_get_local_port_range(&port_min, &port_max);
	src_port = vxlan_src_port(port_min, port_max, skb);

	err = vxlan_xmit_skb(net, vxlan_port->vs, rt, skb,
			     fl.fl4_src, OVS_CB(skb)->tun_key->ipv4_dst,
			     OVS_CB(skb)->tun_key->ipv4_tos,
			     OVS_CB(skb)->tun_key->ipv4_ttl, df,
			     src_port, dst_port,
			     htonl(be64_to_cpu(OVS_CB(skb)->tun_key->tun_id) << 8));
	if (err < 0)
		ip_rt_put(rt);
error:
	return err;
}