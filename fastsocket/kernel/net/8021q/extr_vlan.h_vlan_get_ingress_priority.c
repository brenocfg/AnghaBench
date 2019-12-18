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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct vlan_dev_info {int /*<<< orphan*/ * ingress_priority_map; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int VLAN_PRIO_SHIFT ; 
 struct vlan_dev_info* vlan_dev_info (struct net_device*) ; 

__attribute__((used)) static inline u32 vlan_get_ingress_priority(struct net_device *dev,
					    u16 vlan_tci)
{
	struct vlan_dev_info *vip = vlan_dev_info(dev);

	return vip->ingress_priority_map[(vlan_tci >> VLAN_PRIO_SHIFT) & 0x7];
}