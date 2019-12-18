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
struct iphdr {scalar_t__ tos; } ;
struct TYPE_2__ {scalar_t__ proto; int flags; int encap_limit; } ;
struct ip6_tnl {TYPE_1__ parms; int /*<<< orphan*/  fl; } ;
struct flowi {int fl6_flowlabel; scalar_t__ proto; } ;
typedef  int /*<<< orphan*/  fl ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int __u32 ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_FRAG_NEEDED ; 
 int IP6_TNL_F_IGN_ENCAP_LIMIT ; 
 int IP6_TNL_F_USE_ORIG_TCLASS ; 
 scalar_t__ IPPROTO_IPIP ; 
 int IPV6_TCLASS_MASK ; 
 int IPV6_TCLASS_SHIFT ; 
 int htonl (int) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ip6_tnl_xmit2 (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,struct flowi*,int,int*) ; 
 int /*<<< orphan*/  ip6_tnl_xmit_ctl (struct ip6_tnl*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv4_get_dsfield (struct iphdr*) ; 
 int /*<<< orphan*/  memcpy (struct flowi*,int /*<<< orphan*/ *,int) ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline int
ip4ip6_tnl_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct ip6_tnl *t = netdev_priv(dev);
	struct iphdr  *iph = ip_hdr(skb);
	int encap_limit = -1;
	struct flowi fl;
	__u8 dsfield;
	__u32 mtu;
	int err;

	if ((t->parms.proto != IPPROTO_IPIP && t->parms.proto != 0) ||
	    !ip6_tnl_xmit_ctl(t))
		return -1;

	if (!(t->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT))
		encap_limit = t->parms.encap_limit;

	memcpy(&fl, &t->fl, sizeof (fl));
	fl.proto = IPPROTO_IPIP;

	dsfield = ipv4_get_dsfield(iph);

	if ((t->parms.flags & IP6_TNL_F_USE_ORIG_TCLASS))
		fl.fl6_flowlabel |= htonl((__u32)iph->tos << IPV6_TCLASS_SHIFT)
					  & IPV6_TCLASS_MASK;

	err = ip6_tnl_xmit2(skb, dev, dsfield, &fl, encap_limit, &mtu);
	if (err != 0) {
		/* XXX: send ICMP error even if DF is not set. */
		if (err == -EMSGSIZE)
			icmp_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
				  htonl(mtu));
		return -1;
	}

	return 0;
}