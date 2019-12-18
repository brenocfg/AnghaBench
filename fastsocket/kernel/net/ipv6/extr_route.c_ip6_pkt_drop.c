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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct dst_entry {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPV6_DEST_UNREACH ; 
 int /*<<< orphan*/  IP6_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int IPSTATS_MIB_INADDRERRORS ; 
#define  IPSTATS_MIB_INNOROUTES 129 
#define  IPSTATS_MIB_OUTNOROUTES 128 
 int IPV6_ADDR_ANY ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmpv6_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_dst_idev (struct dst_entry*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static int ip6_pkt_drop(struct sk_buff *skb, u8 code, int ipstats_mib_noroutes)
{
	int type;
	struct dst_entry *dst = skb_dst(skb);
	switch (ipstats_mib_noroutes) {
	case IPSTATS_MIB_INNOROUTES:
		type = ipv6_addr_type(&ipv6_hdr(skb)->daddr);
		if (type == IPV6_ADDR_ANY) {
			IP6_INC_STATS(dev_net(dst->dev), ip6_dst_idev(dst),
				      IPSTATS_MIB_INADDRERRORS);
			break;
		}
		/* FALLTHROUGH */
	case IPSTATS_MIB_OUTNOROUTES:
		IP6_INC_STATS(dev_net(dst->dev), ip6_dst_idev(dst),
			      ipstats_mib_noroutes);
		break;
	}
	icmpv6_send(skb, ICMPV6_DEST_UNREACH, code, 0, skb->dev);
	kfree_skb(skb);
	return 0;
}