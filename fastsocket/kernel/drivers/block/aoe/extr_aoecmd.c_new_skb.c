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
typedef  scalar_t__ ulong ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_AOE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MAX_HEADER ; 
 int /*<<< orphan*/  __constant_htons (int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *
new_skb(ulong len)
{
	struct sk_buff *skb;

	skb = alloc_skb(len + MAX_HEADER, GFP_ATOMIC);
	if (skb) {
		skb_reserve(skb, MAX_HEADER);
		skb_reset_mac_header(skb);
		skb_reset_network_header(skb);
		skb->protocol = __constant_htons(ETH_P_AOE);
		skb_checksum_none_assert(skb);
	}
	return skb;
}