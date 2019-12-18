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
struct ebt_nat_info {unsigned int target; int /*<<< orphan*/  mac; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_dest; } ;

/* Variables and functions */
 unsigned int EBT_DROP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
ebt_dnat_tg(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct ebt_nat_info *info = par->targinfo;

	if (!skb_make_writable(skb, 0))
		return EBT_DROP;

	memcpy(eth_hdr(skb)->h_dest, info->mac, ETH_ALEN);
	return info->target;
}