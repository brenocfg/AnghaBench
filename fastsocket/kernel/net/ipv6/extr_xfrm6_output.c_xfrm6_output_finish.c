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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 TYPE_1__* IP6CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IP6SKB_XFRM_TRANSFORMED ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int xfrm_output (struct sk_buff*) ; 

__attribute__((used)) static int xfrm6_output_finish(struct sk_buff *skb)
{
#ifdef CONFIG_NETFILTER
	IP6CB(skb)->flags |= IP6SKB_XFRM_TRANSFORMED;
#endif

	skb->protocol = htons(ETH_P_IPV6);
	return xfrm_output(skb);
}