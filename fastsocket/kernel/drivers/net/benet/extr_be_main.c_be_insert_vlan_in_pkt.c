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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ vlan_tci; } ;
struct be_adapter {scalar_t__ qnq_vid; scalar_t__ pvid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* __vlan_put_tag (struct sk_buff*,scalar_t__) ; 
 scalar_t__ be_get_tx_vlan_tag (struct be_adapter*,struct sk_buff*) ; 
 scalar_t__ qnq_async_evt_rcvd (struct be_adapter*) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlan_tx_tag_present (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *be_insert_vlan_in_pkt(struct be_adapter *adapter,
					     struct sk_buff *skb,
					     bool *skip_hw_vlan)
{
	u16 vlan_tag = 0;

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (unlikely(!skb))
		return skb;

	if (vlan_tx_tag_present(skb))
		vlan_tag = be_get_tx_vlan_tag(adapter, skb);

	if (qnq_async_evt_rcvd(adapter) && adapter->pvid) {
		if (!vlan_tag)
			vlan_tag = adapter->pvid;
		/* f/w workaround to set skip_hw_vlan = 1, informs the F/W to
		 * skip VLAN insertion
		 */
		if (skip_hw_vlan)
			*skip_hw_vlan = true;
	}

	if (vlan_tag) {
		skb = __vlan_put_tag(skb, vlan_tag);
		if (unlikely(!skb))
			return skb;
		skb->vlan_tci = 0;
	}

	/* Insert the outer VLAN, if any */
	if (adapter->qnq_vid) {
		vlan_tag = adapter->qnq_vid;
		skb = __vlan_put_tag(skb, vlan_tag);
		if (unlikely(!skb))
			return skb;
		if (skip_hw_vlan)
			*skip_hw_vlan = true;
	}

	return skb;
}