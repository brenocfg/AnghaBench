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
struct ipv6hdr {int /*<<< orphan*/  flow_lbl; int /*<<< orphan*/  hop_limit; } ;
struct TYPE_2__ {int ihl; int /*<<< orphan*/  flow_lbl; scalar_t__ optlen; int /*<<< orphan*/  ttl; int /*<<< orphan*/  tos; int /*<<< orphan*/  frag_off; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_DF ; 
 TYPE_1__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_get_dsfield (struct ipv6hdr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int xfrm6_extract_header(struct sk_buff *skb)
{
	struct ipv6hdr *iph = ipv6_hdr(skb);

	XFRM_MODE_SKB_CB(skb)->ihl = sizeof(*iph);
	XFRM_MODE_SKB_CB(skb)->id = 0;
	XFRM_MODE_SKB_CB(skb)->frag_off = htons(IP_DF);
	XFRM_MODE_SKB_CB(skb)->tos = ipv6_get_dsfield(iph);
	XFRM_MODE_SKB_CB(skb)->ttl = iph->hop_limit;
	XFRM_MODE_SKB_CB(skb)->optlen = 0;
	memcpy(XFRM_MODE_SKB_CB(skb)->flow_lbl, iph->flow_lbl,
	       sizeof(XFRM_MODE_SKB_CB(skb)->flow_lbl));

	return 0;
}