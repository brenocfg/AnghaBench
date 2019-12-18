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
struct iphdr {int /*<<< orphan*/  tos; } ;

/* Variables and functions */
 scalar_t__ INET_ECN_is_ce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_ECN_set_ce (struct iphdr*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline void ipip_ecn_decapsulate(const struct iphdr *outer_iph,
					struct sk_buff *skb)
{
	struct iphdr *inner_iph = ip_hdr(skb);

	if (INET_ECN_is_ce(outer_iph->tos))
		IP_ECN_set_ce(inner_iph);
}