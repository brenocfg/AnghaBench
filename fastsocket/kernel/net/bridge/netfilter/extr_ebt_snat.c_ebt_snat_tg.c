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
struct xt_target_param {struct ebt_nat_info* targinfo; } ;
struct sk_buff {int dummy; } ;
struct ebt_nat_info {int target; int /*<<< orphan*/  mac; } ;
struct arphdr {scalar_t__ ar_hln; } ;
typedef  int /*<<< orphan*/  _ah ;
struct TYPE_2__ {scalar_t__ h_proto; int /*<<< orphan*/  h_source; } ;

/* Variables and functions */
 unsigned int EBT_DROP ; 
 unsigned int EBT_VERDICT_BITS ; 
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int NAT_ARP_BIT ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct arphdr* skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,struct arphdr*) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_store_bits (struct sk_buff*,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static unsigned int
ebt_snat_tg(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct ebt_nat_info *info = par->targinfo;

	if (!skb_make_writable(skb, 0))
		return EBT_DROP;

	memcpy(eth_hdr(skb)->h_source, info->mac, ETH_ALEN);
	if (!(info->target & NAT_ARP_BIT) &&
	    eth_hdr(skb)->h_proto == htons(ETH_P_ARP)) {
		const struct arphdr *ap;
		struct arphdr _ah;

		ap = skb_header_pointer(skb, 0, sizeof(_ah), &_ah);
		if (ap == NULL)
			return EBT_DROP;
		if (ap->ar_hln != ETH_ALEN)
			goto out;
		if (skb_store_bits(skb, sizeof(_ah), info->mac,ETH_ALEN))
			return EBT_DROP;
	}
out:
	return info->target | ~EBT_VERDICT_BITS;
}