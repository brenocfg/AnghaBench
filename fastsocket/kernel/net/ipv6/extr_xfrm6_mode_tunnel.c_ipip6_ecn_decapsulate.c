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
struct ipv6hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ INET_ECN_is_ce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP6_ECN_set_ce (struct ipv6hdr*) ; 
 struct ipv6hdr* ipipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_get_dsfield (struct ipv6hdr*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline void ipip6_ecn_decapsulate(struct sk_buff *skb)
{
	struct ipv6hdr *outer_iph = ipv6_hdr(skb);
	struct ipv6hdr *inner_iph = ipipv6_hdr(skb);

	if (INET_ECN_is_ce(ipv6_get_dsfield(outer_iph)))
		IP6_ECN_set_ce(inner_iph);
}