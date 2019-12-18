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
struct arp_pkt {int dummy; } ;

/* Variables and functions */
 scalar_t__ skb_network_header (struct sk_buff const*) ; 

__attribute__((used)) static inline struct arp_pkt *arp_pkt(const struct sk_buff *skb)
{
	return (struct arp_pkt *)skb_network_header(skb);
}