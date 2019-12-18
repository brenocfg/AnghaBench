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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct flowi {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_XFRMINHDRERROR ; 
 int /*<<< orphan*/  XFRM_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 scalar_t__ xfrm_decode_session (struct sk_buff*,struct flowi*,unsigned short) ; 
 scalar_t__ xfrm_lookup (struct net*,struct dst_entry**,struct flowi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int __xfrm_route_forward(struct sk_buff *skb, unsigned short family)
{
	struct net *net = dev_net(skb->dev);
	struct flowi fl;
	struct dst_entry *dst;
	int res;

	if (xfrm_decode_session(skb, &fl, family) < 0) {
		/* XXX: we should have something like FWDHDRERROR here. */
		XFRM_INC_STATS(net, LINUX_MIB_XFRMINHDRERROR);
		return 0;
	}

	dst = skb_dst(skb);

	res = xfrm_lookup(net, &dst, &fl, NULL, 0) == 0;
	skb_dst_set(skb, dst);
	return res;
}