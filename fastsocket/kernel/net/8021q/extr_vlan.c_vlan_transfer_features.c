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
struct net_device {unsigned long features; unsigned long vlan_features; int /*<<< orphan*/  fcoe_ddp_xid; int /*<<< orphan*/  gso_max_size; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 unsigned long NETIF_F_ALL_CSUM ; 
 unsigned long NETIF_F_FCOE_CRC ; 
 unsigned long NETIF_F_GSO ; 
 unsigned long NETIF_F_GSO_MASK ; 
 int NETIF_F_HW_VLAN_TX ; 
 unsigned long NETIF_F_SG ; 
 int VLAN_FLAG_REORDER_HDR ; 
 int /*<<< orphan*/  netdev_features_change (struct net_device*) ; 
 TYPE_1__* vlan_dev_info (struct net_device*) ; 

void vlan_transfer_features(struct net_device *dev, struct net_device *vlandev)
{
	unsigned long old_features = vlandev->features;
	unsigned long new_features = ((old_features & ~dev->vlan_features) |
				      (dev->features & dev->vlan_features));

	/* TX checksum offload cannot work if both TX VLAN tag offload
	 * and reorder_hdr are off.
	 */
	if (!(dev->features & NETIF_F_HW_VLAN_TX) &&
	    !(vlan_dev_info(vlandev)->flags & VLAN_FLAG_REORDER_HDR))
		new_features &= ~(NETIF_F_ALL_CSUM | NETIF_F_SG |
				  NETIF_F_GSO | NETIF_F_GSO_MASK |
				  NETIF_F_FCOE_CRC);
	vlandev->features = new_features;
	vlandev->gso_max_size = dev->gso_max_size;
#if defined(CONFIG_FCOE) || defined(CONFIG_FCOE_MODULE)
	vlandev->fcoe_ddp_xid = dev->fcoe_ddp_xid;
#endif
	if (old_features != vlandev->features)
		netdev_features_change(vlandev);
}