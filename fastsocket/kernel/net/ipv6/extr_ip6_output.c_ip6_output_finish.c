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
struct dst_entry {int /*<<< orphan*/  dev; TYPE_1__* neighbour; scalar_t__ hh; } ;
struct TYPE_2__ {int (* output ) (struct sk_buff*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IP6_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTNOROUTES ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_dst_idev (struct dst_entry*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int neigh_hh_output (scalar_t__,struct sk_buff*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 

__attribute__((used)) static int ip6_output_finish(struct sk_buff *skb)
{
	struct dst_entry *dst = skb_dst(skb);

	if (dst->hh)
		return neigh_hh_output(dst->hh, skb);
	else if (dst->neighbour)
		return dst->neighbour->output(skb);

	IP6_INC_STATS_BH(dev_net(dst->dev),
			 ip6_dst_idev(dst), IPSTATS_MIB_OUTNOROUTES);
	kfree_skb(skb);
	return -EINVAL;

}