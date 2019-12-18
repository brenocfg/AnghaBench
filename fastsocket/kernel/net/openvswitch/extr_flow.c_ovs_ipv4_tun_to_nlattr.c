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
struct sk_buff {int dummy; } ;
struct ovs_key_ipv4_tunnel {int tun_flags; scalar_t__ ipv4_ttl; scalar_t__ ipv4_tos; scalar_t__ ipv4_dst; scalar_t__ ipv4_src; int /*<<< orphan*/  tun_id; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  OVS_KEY_ATTR_TUNNEL ; 
 int /*<<< orphan*/  OVS_TUNNEL_KEY_ATTR_CSUM ; 
 int /*<<< orphan*/  OVS_TUNNEL_KEY_ATTR_DONT_FRAGMENT ; 
 int /*<<< orphan*/  OVS_TUNNEL_KEY_ATTR_ID ; 
 int /*<<< orphan*/  OVS_TUNNEL_KEY_ATTR_IPV4_DST ; 
 int /*<<< orphan*/  OVS_TUNNEL_KEY_ATTR_IPV4_SRC ; 
 int /*<<< orphan*/  OVS_TUNNEL_KEY_ATTR_TOS ; 
 int /*<<< orphan*/  OVS_TUNNEL_KEY_ATTR_TTL ; 
 int TUNNEL_CSUM ; 
 int TUNNEL_DONT_FRAGMENT ; 
 int TUNNEL_KEY ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_be64 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 

int ovs_ipv4_tun_to_nlattr(struct sk_buff *skb,
			   const struct ovs_key_ipv4_tunnel *tun_key)
{
	struct nlattr *nla;

	nla = nla_nest_start(skb, OVS_KEY_ATTR_TUNNEL);
	if (!nla)
		return -EMSGSIZE;

	if (tun_key->tun_flags & TUNNEL_KEY &&
	    nla_put_be64(skb, OVS_TUNNEL_KEY_ATTR_ID, tun_key->tun_id))
		return -EMSGSIZE;
	if (tun_key->ipv4_src &&
	    nla_put_be32(skb, OVS_TUNNEL_KEY_ATTR_IPV4_SRC, tun_key->ipv4_src))
		return -EMSGSIZE;
	if (nla_put_be32(skb, OVS_TUNNEL_KEY_ATTR_IPV4_DST, tun_key->ipv4_dst))
		return -EMSGSIZE;
	if (tun_key->ipv4_tos &&
	    nla_put_u8(skb, OVS_TUNNEL_KEY_ATTR_TOS, tun_key->ipv4_tos))
		return -EMSGSIZE;
	if (nla_put_u8(skb, OVS_TUNNEL_KEY_ATTR_TTL, tun_key->ipv4_ttl))
		return -EMSGSIZE;
	if ((tun_key->tun_flags & TUNNEL_DONT_FRAGMENT) &&
		nla_put_flag(skb, OVS_TUNNEL_KEY_ATTR_DONT_FRAGMENT))
		return -EMSGSIZE;
	if ((tun_key->tun_flags & TUNNEL_CSUM) &&
		nla_put_flag(skb, OVS_TUNNEL_KEY_ATTR_CSUM))
		return -EMSGSIZE;

	nla_nest_end(skb, nla);
	return 0;
}