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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct sk_buff {int data; int /*<<< orphan*/  dev; int /*<<< orphan*/  len; } ;
struct ipv6hdr {scalar_t__ nexthdr; int /*<<< orphan*/  daddr; } ;
struct inet6_skb_parm {int flags; int ra; } ;
struct icmp6hdr {int icmp6_type; } ;
struct TYPE_8__ {TYPE_1__* devconf_all; } ;
struct TYPE_10__ {TYPE_2__ ipv6; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {scalar_t__ mc_forwarding; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  ICMPV6_MGM_QUERY 131 
#define  ICMPV6_MGM_REDUCTION 130 
#define  ICMPV6_MGM_REPORT 129 
#define  ICMPV6_MLD2_REPORT 128 
 struct inet6_skb_parm* IP6CB (struct sk_buff*) ; 
 int IP6SKB_FORWARDED ; 
 int /*<<< orphan*/  IP6_UPD_PO_STATS_BH (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IPPROTO_ICMPV6 ; 
 int /*<<< orphan*/  IPSTATS_MIB_INMCAST ; 
 int IPV6_ADDR_LINKLOCAL ; 
 TYPE_5__* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_dst_idev (TYPE_3__*) ; 
 int /*<<< orphan*/  ip6_input (struct sk_buff*) ; 
 int /*<<< orphan*/  ip6_mr_input (struct sk_buff*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 int ipv6_chk_mcast_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_ext_hdr (scalar_t__) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int ipv6_skip_exthdr (struct sk_buff*,int,scalar_t__*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_3__* skb_dst (struct sk_buff*) ; 
 scalar_t__* skb_network_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int ip6_mc_input(struct sk_buff *skb)
{
	struct ipv6hdr *hdr;
	int deliver;

	IP6_UPD_PO_STATS_BH(dev_net(skb_dst(skb)->dev),
			 ip6_dst_idev(skb_dst(skb)), IPSTATS_MIB_INMCAST,
			 skb->len);

	hdr = ipv6_hdr(skb);
	deliver = ipv6_chk_mcast_addr(skb->dev, &hdr->daddr, NULL);

#ifdef CONFIG_IPV6_MROUTE
	/*
	 *      IPv6 multicast router mode is now supported ;)
	 */
	if (dev_net(skb->dev)->ipv6.devconf_all->mc_forwarding &&
	    !(ipv6_addr_type(&hdr->daddr) & IPV6_ADDR_LINKLOCAL) &&
	    likely(!(IP6CB(skb)->flags & IP6SKB_FORWARDED))) {
		/*
		 * Okay, we try to forward - split and duplicate
		 * packets.
		 */
		struct sk_buff *skb2;
		struct inet6_skb_parm *opt = IP6CB(skb);

		/* Check for MLD */
		if (unlikely(opt->ra)) {
			/* Check if this is a mld message */
			u8 *ptr = skb_network_header(skb) + opt->ra;
			struct icmp6hdr *icmp6;
			u8 nexthdr = hdr->nexthdr;
			int offset;

			/* Check if the value of Router Alert
			 * is for MLD (0x0000).
			 */
			if ((ptr[2] | ptr[3]) == 0) {
				deliver = 0;

				if (!ipv6_ext_hdr(nexthdr)) {
					/* BUG */
					goto out;
				}
				offset = ipv6_skip_exthdr(skb, sizeof(*hdr),
							  &nexthdr);
				if (offset < 0)
					goto out;

				if (nexthdr != IPPROTO_ICMPV6)
					goto out;

				if (!pskb_may_pull(skb, (skb_network_header(skb) +
						   offset + 1 - skb->data)))
					goto out;

				icmp6 = (struct icmp6hdr *)(skb_network_header(skb) + offset);

				switch (icmp6->icmp6_type) {
				case ICMPV6_MGM_QUERY:
				case ICMPV6_MGM_REPORT:
				case ICMPV6_MGM_REDUCTION:
				case ICMPV6_MLD2_REPORT:
					deliver = 1;
					break;
				}
				goto out;
			}
			/* unknown RA - process it normally */
		}

		if (deliver)
			skb2 = skb_clone(skb, GFP_ATOMIC);
		else {
			skb2 = skb;
			skb = NULL;
		}

		if (skb2) {
			ip6_mr_input(skb2);
		}
	}
out:
#endif
	if (likely(deliver))
		ip6_input(skb);
	else {
		/* discard */
		kfree_skb(skb);
	}

	return 0;
}