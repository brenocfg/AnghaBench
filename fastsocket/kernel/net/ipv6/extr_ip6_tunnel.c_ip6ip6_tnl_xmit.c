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
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct ipv6_tlv_tnl_enc_lim {int encap_limit; } ;
struct TYPE_2__ {scalar_t__ proto; int flags; int encap_limit; } ;
struct ip6_tnl {TYPE_1__ parms; int /*<<< orphan*/  fl; } ;
struct flowi {int fl6_flowlabel; scalar_t__ proto; } ;
typedef  int /*<<< orphan*/  fl ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  size_t __u32 ;
typedef  size_t __u16 ;
typedef  int __be32 ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ICMPV6_HDR_FIELD ; 
 int /*<<< orphan*/  ICMPV6_PARAMPROB ; 
 int /*<<< orphan*/  ICMPV6_PKT_TOOBIG ; 
 int IP6_TNL_F_IGN_ENCAP_LIMIT ; 
 int IP6_TNL_F_USE_ORIG_FLOWLABEL ; 
 int IP6_TNL_F_USE_ORIG_TCLASS ; 
 scalar_t__ IPPROTO_IPV6 ; 
 int IPV6_FLOWLABEL_MASK ; 
 int IPV6_TCLASS_MASK ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,struct net_device*) ; 
 scalar_t__ ip6_tnl_addr_conflict (struct ip6_tnl*,struct ipv6hdr*) ; 
 int ip6_tnl_xmit2 (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,struct flowi*,int,size_t*) ; 
 int /*<<< orphan*/  ip6_tnl_xmit_ctl (struct ip6_tnl*) ; 
 int /*<<< orphan*/  ipv6_get_dsfield (struct ipv6hdr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (struct flowi*,int /*<<< orphan*/ *,int) ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 
 size_t parse_tlv_tnl_enc_lim (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static inline int
ip6ip6_tnl_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ip6_tnl *t = netdev_priv(dev);
	struct ipv6hdr *ipv6h = ipv6_hdr(skb);
	int encap_limit = -1;
	__u16 offset;
	struct flowi fl;
	__u8 dsfield;
	__u32 mtu;
	int err;

	if ((t->parms.proto != IPPROTO_IPV6 && t->parms.proto != 0) ||
	    !ip6_tnl_xmit_ctl(t) || ip6_tnl_addr_conflict(t, ipv6h))
		return -1;

	offset = parse_tlv_tnl_enc_lim(skb, skb_network_header(skb));
	if (offset > 0) {
		struct ipv6_tlv_tnl_enc_lim *tel;
		tel = (struct ipv6_tlv_tnl_enc_lim *)&skb_network_header(skb)[offset];
		if (tel->encap_limit == 0) {
			icmpv6_send(skb, ICMPV6_PARAMPROB,
				    ICMPV6_HDR_FIELD, offset + 2, skb->dev);
			return -1;
		}
		encap_limit = tel->encap_limit - 1;
	} else if (!(t->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT))
		encap_limit = t->parms.encap_limit;

	memcpy(&fl, &t->fl, sizeof (fl));
	fl.proto = IPPROTO_IPV6;

	dsfield = ipv6_get_dsfield(ipv6h);
	if ((t->parms.flags & IP6_TNL_F_USE_ORIG_TCLASS))
		fl.fl6_flowlabel |= (*(__be32 *) ipv6h & IPV6_TCLASS_MASK);
	if ((t->parms.flags & IP6_TNL_F_USE_ORIG_FLOWLABEL))
		fl.fl6_flowlabel |= (*(__be32 *) ipv6h & IPV6_FLOWLABEL_MASK);

	err = ip6_tnl_xmit2(skb, dev, dsfield, &fl, encap_limit, &mtu);
	if (err != 0) {
		if (err == -EMSGSIZE)
			icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu, dev);
		return -1;
	}

	return 0;
}