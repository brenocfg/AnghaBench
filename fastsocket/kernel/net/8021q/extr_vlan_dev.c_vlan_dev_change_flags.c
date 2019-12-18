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
typedef  int u32 ;
struct vlan_dev_info {int flags; TYPE_1__* real_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int features; int vlan_features; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int NETIF_F_ALL_CSUM ; 
 int NETIF_F_HW_VLAN_TX ; 
 int VLAN_FLAG_GVRP ; 
 int VLAN_FLAG_REORDER_HDR ; 
 scalar_t__ netif_running (struct net_device*) ; 
 struct vlan_dev_info* vlan_dev_info (struct net_device*) ; 
 int /*<<< orphan*/  vlan_gvrp_request_join (struct net_device*) ; 
 int /*<<< orphan*/  vlan_gvrp_request_leave (struct net_device*) ; 
 int /*<<< orphan*/  vlan_transfer_features (TYPE_1__*,struct net_device*) ; 

int vlan_dev_change_flags(struct net_device *dev, u32 flags, u32 mask)
{
	struct vlan_dev_info *vlan = vlan_dev_info(dev);
	u32 old_flags = vlan->flags;

	if (mask & ~(VLAN_FLAG_REORDER_HDR | VLAN_FLAG_GVRP))
		return -EINVAL;

	/* TX checksum offload cannot work if both TX VLAN tag offload
	 * and reorder_hdr are off.  To avoid racing with the TX path,
	 * do not allow the device to enter or exit this state while
	 * it is running.
	 */
	if (netif_running(dev) &&
	    !(vlan->real_dev->features & NETIF_F_HW_VLAN_TX) &&
	    (vlan->real_dev->vlan_features & NETIF_F_ALL_CSUM) &&
	    ((flags ^ old_flags) & VLAN_FLAG_REORDER_HDR))
		return -EBUSY;

	vlan->flags = (old_flags & ~mask) | (flags & mask);

	if (netif_running(dev) && (vlan->flags ^ old_flags) & VLAN_FLAG_GVRP) {
		if (vlan->flags & VLAN_FLAG_GVRP)
			vlan_gvrp_request_join(dev);
		else
			vlan_gvrp_request_leave(dev);
	}
	if ((vlan->flags ^ old_flags) & VLAN_FLAG_REORDER_HDR)
		vlan_transfer_features(vlan->real_dev, dev);
	return 0;
}