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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ data; int /*<<< orphan*/  csum; } ;
struct ovs_action_push_vlan {int /*<<< orphan*/  vlan_tci; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_COMPLETE ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  VLAN_HLEN ; 
 int VLAN_TAG_PRESENT ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __vlan_put_tag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_tx_tag_get (struct sk_buff*) ; 
 int /*<<< orphan*/  vlan_tx_tag_present (struct sk_buff*) ; 

__attribute__((used)) static int push_vlan(struct sk_buff *skb, const struct ovs_action_push_vlan *vlan)
{
	if (unlikely(vlan_tx_tag_present(skb))) {
		u16 current_tag;

		/* push down current VLAN tag */
		current_tag = vlan_tx_tag_get(skb);

		if (!__vlan_put_tag(skb, current_tag))
			return -ENOMEM;

		if (skb->ip_summed == CHECKSUM_COMPLETE)
			skb->csum = csum_add(skb->csum, csum_partial(skb->data
					+ (2 * ETH_ALEN), VLAN_HLEN, 0));

	}
	__vlan_hwaccel_put_tag(skb, ntohs(vlan->vlan_tci) & ~VLAN_TAG_PRESENT);
	return 0;
}