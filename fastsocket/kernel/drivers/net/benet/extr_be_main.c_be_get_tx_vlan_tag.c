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
typedef  int u8 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct be_adapter {int vlan_prio_bmap; int recommended_prio; } ;

/* Variables and functions */
 int VLAN_PRIO_MASK ; 
 int VLAN_PRIO_SHIFT ; 
 int vlan_tx_tag_get (struct sk_buff*) ; 

__attribute__((used)) static inline u16 be_get_tx_vlan_tag(struct be_adapter *adapter,
					struct sk_buff *skb)
{
	u8 vlan_prio;
	u16 vlan_tag;

	vlan_tag = vlan_tx_tag_get(skb);
	vlan_prio = (vlan_tag & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;
	/* If vlan priority provided by OS is NOT in available bmap */
	if (!(adapter->vlan_prio_bmap & (1 << vlan_prio)))
		vlan_tag = (vlan_tag & ~VLAN_PRIO_MASK) |
				adapter->recommended_prio;

	return vlan_tag;
}