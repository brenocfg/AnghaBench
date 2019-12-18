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
struct sk_buff {scalar_t__ protocol; } ;
struct iphdr {int /*<<< orphan*/  tos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ INET_ECN_is_ce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP6_ECN_set_ce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_ECN_set_ce (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline void ipgre_ecn_decapsulate(const struct iphdr *iph, struct sk_buff *skb)
{
	if (INET_ECN_is_ce(iph->tos)) {
		if (skb->protocol == htons(ETH_P_IP)) {
			IP_ECN_set_ce(ip_hdr(skb));
		} else if (skb->protocol == htons(ETH_P_IPV6)) {
			IP6_ECN_set_ce(ipv6_hdr(skb));
		}
	}
}