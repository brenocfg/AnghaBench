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
struct TYPE_2__ {int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMPV6_UNK_OPTION ; 
 int /*<<< orphan*/  icmpv6_param_prob (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipv6_addr_is_multicast (int /*<<< orphan*/ *) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int* skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static int ip6_tlvopt_unknown(struct sk_buff *skb, int optoff)
{
	switch ((skb_network_header(skb)[optoff] & 0xC0) >> 6) {
	case 0: /* ignore */
		return 1;

	case 1: /* drop packet */
		break;

	case 3: /* Send ICMP if not a multicast address and drop packet */
		/* Actually, it is redundant check. icmp_send
		   will recheck in any case.
		 */
		if (ipv6_addr_is_multicast(&ipv6_hdr(skb)->daddr))
			break;
	case 2: /* send ICMP PARM PROB regardless and drop packet */
		icmpv6_param_prob(skb, ICMPV6_UNK_OPTION, optoff);
		return 0;
	}

	kfree_skb(skb);
	return 0;
}