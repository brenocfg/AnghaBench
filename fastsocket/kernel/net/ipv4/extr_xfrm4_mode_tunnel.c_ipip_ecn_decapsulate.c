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
struct iphdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tos; } ;

/* Variables and functions */
 scalar_t__ INET_ECN_is_ce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_ECN_set_ce (struct iphdr*) ; 
 TYPE_1__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 struct iphdr* ipip_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline void ipip_ecn_decapsulate(struct sk_buff *skb)
{
	struct iphdr *inner_iph = ipip_hdr(skb);

	if (INET_ECN_is_ce(XFRM_MODE_SKB_CB(skb)->tos))
		IP_ECN_set_ce(inner_iph);
}