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
struct sk_buff {unsigned int len; scalar_t__ protocol; } ;

/* Variables and functions */
 unsigned int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ VLAN_HLEN ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned packet_length(const struct sk_buff *skb)
{
	unsigned length = skb->len - ETH_HLEN;

	if (skb->protocol == htons(ETH_P_8021Q))
		length -= VLAN_HLEN;

	return length;
}