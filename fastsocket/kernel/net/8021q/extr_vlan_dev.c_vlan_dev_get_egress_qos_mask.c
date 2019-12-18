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
typedef  int /*<<< orphan*/  u16 ;
struct vlan_priority_tci_mapping {int priority; struct vlan_priority_tci_mapping* next; int /*<<< orphan*/  vlan_qos; } ;
struct sk_buff {int priority; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct vlan_priority_tci_mapping** egress_priority_map; } ;

/* Variables and functions */
 TYPE_1__* vlan_dev_info (struct net_device*) ; 

__attribute__((used)) static inline u16
vlan_dev_get_egress_qos_mask(struct net_device *dev, struct sk_buff *skb)
{
	struct vlan_priority_tci_mapping *mp;

	mp = vlan_dev_info(dev)->egress_priority_map[(skb->priority & 0xF)];
	while (mp) {
		if (mp->priority == skb->priority) {
			return mp->vlan_qos; /* This should already be shifted
					      * to mask correctly with the
					      * VLAN's TCI */
		}
		mp = mp->next;
	}
	return 0;
}