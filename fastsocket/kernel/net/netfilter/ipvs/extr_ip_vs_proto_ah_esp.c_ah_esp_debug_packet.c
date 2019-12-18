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
struct ip_vs_protocol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  ah_esp_debug_packet_v4 (struct ip_vs_protocol*,struct sk_buff const*,int,char const*) ; 
 int /*<<< orphan*/  ah_esp_debug_packet_v6 (struct ip_vs_protocol*,struct sk_buff const*,int,char const*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ah_esp_debug_packet(struct ip_vs_protocol *pp, const struct sk_buff *skb,
		    int offset, const char *msg)
{
#ifdef CONFIG_IP_VS_IPV6
	if (skb->protocol == htons(ETH_P_IPV6))
		ah_esp_debug_packet_v6(pp, skb, offset, msg);
	else
#endif
		ah_esp_debug_packet_v4(pp, skb, offset, msg);
}