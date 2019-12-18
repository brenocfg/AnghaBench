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
struct sk_buff {int dummy; } ;
struct icmp6hdr {int icmp6_type; } ;

/* Variables and functions */
#define  ICMPV6_MGM_QUERY 131 
#define  ICMPV6_MGM_REDUCTION 130 
#define  ICMPV6_MGM_REPORT 129 
#define  ICMPV6_MLD2_REPORT 128 
 int IPPROTO_ICMPV6 ; 
 struct icmp6hdr* icmp6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 

int ipv6_is_mld(struct sk_buff *skb, int nexthdr)
{
	struct icmp6hdr *pic;

	if (nexthdr != IPPROTO_ICMPV6)
		return 0;

	if (!pskb_may_pull(skb, sizeof(struct icmp6hdr)))
		return 0;

	pic = icmp6_hdr(skb);

	switch (pic->icmp6_type) {
	case ICMPV6_MGM_QUERY:
	case ICMPV6_MGM_REPORT:
	case ICMPV6_MGM_REDUCTION:
	case ICMPV6_MLD2_REPORT:
		return 1;
	default:
		break;
	}
	return 0;
}