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
struct ipv6hdr {int version; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  nexthdr; int /*<<< orphan*/  flow_lbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; int /*<<< orphan*/  protocol; int /*<<< orphan*/  flow_lbl; } ;

/* Variables and functions */
 TYPE_1__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_change_dsfield (struct ipv6hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xfrm6_beet_make_header(struct sk_buff *skb)
{
	struct ipv6hdr *iph = ipv6_hdr(skb);

	iph->version = 6;

	memcpy(iph->flow_lbl, XFRM_MODE_SKB_CB(skb)->flow_lbl,
	       sizeof(iph->flow_lbl));
	iph->nexthdr = XFRM_MODE_SKB_CB(skb)->protocol;

	ipv6_change_dsfield(iph, 0, XFRM_MODE_SKB_CB(skb)->tos);
	iph->hop_limit = XFRM_MODE_SKB_CB(skb)->ttl;
}