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
struct vlan_group {scalar_t__ nr_vlans; int /*<<< orphan*/  rcu; int /*<<< orphan*/  hlist; } ;
struct vlan_dev_info {scalar_t__ vlan_id; struct net_device* real_dev; } ;
struct net_device_ops {int /*<<< orphan*/  (* ndo_vlan_rx_register ) (struct net_device*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ndo_vlan_rx_kill_vid ) (struct net_device*,scalar_t__) ;} ;
struct net_device {int features; struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NETIF_F_HW_VLAN_FILTER ; 
 int NETIF_F_HW_VLAN_RX ; 
 struct vlan_group* __vlan_find_group (struct net_device*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 
 struct vlan_dev_info* vlan_dev_info (struct net_device*) ; 
 int /*<<< orphan*/  vlan_group_set_device (struct vlan_group*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_gvrp_uninit_applicant (struct net_device*) ; 
 int /*<<< orphan*/  vlan_rcu_free ; 

void unregister_vlan_dev(struct net_device *dev)
{
	struct vlan_dev_info *vlan = vlan_dev_info(dev);
	struct net_device *real_dev = vlan->real_dev;
	const struct net_device_ops *ops = real_dev->netdev_ops;
	struct vlan_group *grp;
	u16 vlan_id = vlan->vlan_id;

	ASSERT_RTNL();

	grp = __vlan_find_group(real_dev);
	BUG_ON(!grp);

	/* Take it out of our own structures, but be sure to interlock with
	 * HW accelerating devices or SW vlan input packet processing if
	 * VLAN is not 0 (leave it there for 802.1p).
	 */
	if (vlan_id && (real_dev->features & NETIF_F_HW_VLAN_FILTER))
		ops->ndo_vlan_rx_kill_vid(real_dev, vlan_id);

	vlan_group_set_device(grp, vlan_id, NULL);
	grp->nr_vlans--;

	synchronize_net();

	unregister_netdevice(dev);

	/* If the group is now empty, kill off the group. */
	if (grp->nr_vlans == 0) {
		vlan_gvrp_uninit_applicant(real_dev);

		if (real_dev->features & NETIF_F_HW_VLAN_RX)
			ops->ndo_vlan_rx_register(real_dev, NULL);

		hlist_del_rcu(&grp->hlist);

		/* Free the group, after all cpu's are done. */
		call_rcu(&grp->rcu, vlan_rcu_free);
	}

	/* Get rid of the vlan's reference to real_dev */
	dev_put(real_dev);
}