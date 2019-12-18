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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct vlan_dev_info {scalar_t__* ingress_priority_map; int /*<<< orphan*/  nr_ingress_mappings; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct vlan_dev_info* vlan_dev_info (struct net_device const*) ; 

void vlan_dev_set_ingress_priority(const struct net_device *dev,
				   u32 skb_prio, u16 vlan_prio)
{
	struct vlan_dev_info *vlan = vlan_dev_info(dev);

	if (vlan->ingress_priority_map[vlan_prio & 0x7] && !skb_prio)
		vlan->nr_ingress_mappings--;
	else if (!vlan->ingress_priority_map[vlan_prio & 0x7] && skb_prio)
		vlan->nr_ingress_mappings++;

	vlan->ingress_priority_map[vlan_prio & 0x7] = skb_prio;
}