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
struct vlan_group {int nr_vlans; } ;
struct notifier_block {int dummy; } ;
struct net_device {int features; int flags; int /*<<< orphan*/  reg_state; int /*<<< orphan*/  mtu; TYPE_1__* netdev_ops; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ndo_vlan_rx_add_vid ) (struct net_device*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int IFF_UP ; 
#define  NETDEV_CHANGE 134 
#define  NETDEV_CHANGEADDR 133 
#define  NETDEV_CHANGEMTU 132 
#define  NETDEV_DOWN 131 
#define  NETDEV_FEAT_CHANGE 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NETIF_F_HW_VLAN_FILTER ; 
 int /*<<< orphan*/  NETREG_UNREGISTERING ; 
 int NOTIFY_DONE ; 
 int VLAN_GROUP_ARRAY_LEN ; 
 int /*<<< orphan*/  __vlan_device_event (struct net_device*,unsigned long) ; 
 struct vlan_group* __vlan_find_group (struct net_device*) ; 
 int /*<<< orphan*/  dev_change_flags (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_set_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_slave_event (struct net_device*,int) ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  netif_stacked_transfer_operstate (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_vlan_dev (struct net_device*) ; 
 struct net_device* vlan_group_get_device (struct vlan_group*,int) ; 
 int /*<<< orphan*/  vlan_sync_address (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  vlan_transfer_features (struct net_device*,struct net_device*) ; 

__attribute__((used)) static int vlan_device_event(struct notifier_block *unused, unsigned long event,
			     void *ptr)
{
	struct net_device *dev = ptr;
	struct vlan_group *grp;
	int i, flgs;
	struct net_device *vlandev;

	if (is_vlan_dev(dev))
		__vlan_device_event(dev, event);

	if ((event == NETDEV_UP) &&
	    (dev->features & NETIF_F_HW_VLAN_FILTER) &&
	    dev->netdev_ops->ndo_vlan_rx_add_vid) {
		pr_info("8021q: adding VLAN 0 to HW filter on device %s\n",
			dev->name);
		dev->netdev_ops->ndo_vlan_rx_add_vid(dev, 0);
	}

	grp = __vlan_find_group(dev);
	if (!grp)
		goto out;

	/* It is OK that we do not hold the group lock right now,
	 * as we run under the RTNL lock.
	 */

	switch (event) {
	case NETDEV_CHANGE:
		/* Propagate real device state to vlan devices */
		for (i = 0; i < VLAN_GROUP_ARRAY_LEN; i++) {
			if (ignore_slave_event(dev, i))
				continue;
			vlandev = vlan_group_get_device(grp, i);
			if (!vlandev)
				continue;

			netif_stacked_transfer_operstate(dev, vlandev);
		}
		break;

	case NETDEV_CHANGEADDR:
		/* Adjust unicast filters on underlying device */
		for (i = 0; i < VLAN_GROUP_ARRAY_LEN; i++) {
			if (ignore_slave_event(dev, i))
				continue;
			vlandev = vlan_group_get_device(grp, i);
			if (!vlandev)
				continue;

			flgs = vlandev->flags;
			if (!(flgs & IFF_UP))
				continue;

			vlan_sync_address(dev, vlandev);
		}
		break;

	case NETDEV_CHANGEMTU:
		for (i = 0; i < VLAN_GROUP_ARRAY_LEN; i++) {
			if (ignore_slave_event(dev, i))
				continue;
			vlandev = vlan_group_get_device(grp, i);
			if (!vlandev)
				continue;

			if (vlandev->mtu <= dev->mtu)
				continue;

			dev_set_mtu(vlandev, dev->mtu);
		}
		break;

	case NETDEV_FEAT_CHANGE:
		/* Propagate device features to underlying device */
		for (i = 0; i < VLAN_GROUP_ARRAY_LEN; i++) {
			if (ignore_slave_event(dev, i))
				continue;
			vlandev = vlan_group_get_device(grp, i);
			if (!vlandev)
				continue;

			vlan_transfer_features(dev, vlandev);
		}

		break;

	case NETDEV_DOWN:
		/* Put all VLANs for this dev in the down state too.  */
		for (i = 0; i < VLAN_GROUP_ARRAY_LEN; i++) {
			if (ignore_slave_event(dev, i))
				continue;
			vlandev = vlan_group_get_device(grp, i);
			if (!vlandev)
				continue;

			flgs = vlandev->flags;
			if (!(flgs & IFF_UP))
				continue;

			dev_change_flags(vlandev, flgs & ~IFF_UP);
			netif_stacked_transfer_operstate(dev, vlandev);
		}
		break;

	case NETDEV_UP:
		/* Put all VLANs for this dev in the up state too.  */
		for (i = 0; i < VLAN_GROUP_ARRAY_LEN; i++) {
			if (ignore_slave_event(dev, i))
				continue;
			vlandev = vlan_group_get_device(grp, i);
			if (!vlandev)
				continue;

			flgs = vlandev->flags;
			if (flgs & IFF_UP)
				continue;

			dev_change_flags(vlandev, flgs | IFF_UP);
			netif_stacked_transfer_operstate(dev, vlandev);
		}
		break;

	case NETDEV_UNREGISTER:
		/* twiddle thumbs on netns device moves */
		if (dev->reg_state != NETREG_UNREGISTERING)
			break;

		/* Delete all VLANs for this dev. */
		for (i = 0; i < VLAN_GROUP_ARRAY_LEN; i++) {
			if (ignore_slave_event(dev, i))
				continue;
			vlandev = vlan_group_get_device(grp, i);
			if (!vlandev)
				continue;

			/* unregistration of last vlan destroys group, abort
			 * afterwards */
			if (grp->nr_vlans == 1)
				i = VLAN_GROUP_ARRAY_LEN;

			unregister_vlan_dev(vlandev);
		}
		break;
	}

out:
	return NOTIFY_DONE;
}