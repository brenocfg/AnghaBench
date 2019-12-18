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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int ttl; int tos; int frag_off; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct ip_tunnel_parm {TYPE_1__ iph; int /*<<< orphan*/  o_key; int /*<<< orphan*/  i_key; int /*<<< orphan*/  o_flags; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  link; } ;
struct ip_tunnel {struct ip_tunnel_parm parms; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_GRE_IFLAGS ; 
 int /*<<< orphan*/  IFLA_GRE_IKEY ; 
 int /*<<< orphan*/  IFLA_GRE_LINK ; 
 int /*<<< orphan*/  IFLA_GRE_LOCAL ; 
 int /*<<< orphan*/  IFLA_GRE_OFLAGS ; 
 int /*<<< orphan*/  IFLA_GRE_OKEY ; 
 int /*<<< orphan*/  IFLA_GRE_PMTUDISC ; 
 int /*<<< orphan*/  IFLA_GRE_REMOTE ; 
 int /*<<< orphan*/  IFLA_GRE_TOS ; 
 int /*<<< orphan*/  IFLA_GRE_TTL ; 
 int /*<<< orphan*/  IP_DF ; 
 int htons (int /*<<< orphan*/ ) ; 
 struct ip_tunnel* netdev_priv (struct net_device const*) ; 
 scalar_t__ nla_put_be16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tnl_flags_to_gre_flags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipgre_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	struct ip_tunnel *t = netdev_priv(dev);
	struct ip_tunnel_parm *p = &t->parms;

	if (nla_put_u32(skb, IFLA_GRE_LINK, p->link) ||
	    nla_put_be16(skb, IFLA_GRE_IFLAGS, tnl_flags_to_gre_flags(p->i_flags)) ||
	    nla_put_be16(skb, IFLA_GRE_OFLAGS, tnl_flags_to_gre_flags(p->o_flags)) ||
	    nla_put_be32(skb, IFLA_GRE_IKEY, p->i_key) ||
	    nla_put_be32(skb, IFLA_GRE_OKEY, p->o_key) ||
	    nla_put_be32(skb, IFLA_GRE_LOCAL, p->iph.saddr) ||
	    nla_put_be32(skb, IFLA_GRE_REMOTE, p->iph.daddr) ||
	    nla_put_u8(skb, IFLA_GRE_TTL, p->iph.ttl) ||
	    nla_put_u8(skb, IFLA_GRE_TOS, p->iph.tos) ||
	    nla_put_u8(skb, IFLA_GRE_PMTUDISC,
		       !!(p->iph.frag_off & htons(IP_DF))))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -EMSGSIZE;
}