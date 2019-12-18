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
struct vlan_group {int /*<<< orphan*/  rcu; int /*<<< orphan*/  hlist; int /*<<< orphan*/  nr_vlans; } ;
struct vlan_dev_info {int /*<<< orphan*/  vlan_id; struct net_device* real_dev; } ;
struct net_device_ops {int /*<<< orphan*/  (* ndo_vlan_rx_add_vid ) (struct net_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ndo_vlan_rx_register ) (struct net_device*,struct vlan_group*) ;} ;
struct net_device {int features; struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int NETIF_F_HW_VLAN_FILTER ; 
 int NETIF_F_HW_VLAN_RX ; 
 struct vlan_group* __vlan_find_group (struct net_device*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linkwatch_fire_event (struct net_device*) ; 
 int /*<<< orphan*/  netif_stacked_transfer_operstate (struct net_device*,struct net_device*) ; 
 int register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct vlan_group*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,int /*<<< orphan*/ ) ; 
 struct vlan_dev_info* vlan_dev_info (struct net_device*) ; 
 struct vlan_group* vlan_group_alloc (struct net_device*) ; 
 int vlan_group_prealloc_vid (struct vlan_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_group_set_device (struct vlan_group*,int /*<<< orphan*/ ,struct net_device*) ; 
 int vlan_gvrp_init_applicant (struct net_device*) ; 
 int /*<<< orphan*/  vlan_gvrp_uninit_applicant (struct net_device*) ; 
 int /*<<< orphan*/  vlan_rcu_free ; 

int register_vlan_dev(struct net_device *dev)
{
	struct vlan_dev_info *vlan = vlan_dev_info(dev);
	struct net_device *real_dev = vlan->real_dev;
	const struct net_device_ops *ops = real_dev->netdev_ops;
	u16 vlan_id = vlan->vlan_id;
	struct vlan_group *grp, *ngrp = NULL;
	int err;

	grp = __vlan_find_group(real_dev);
	if (!grp) {
		ngrp = grp = vlan_group_alloc(real_dev);
		if (!grp)
			return -ENOBUFS;
		err = vlan_gvrp_init_applicant(real_dev);
		if (err < 0)
			goto out_free_group;
	}

	err = vlan_group_prealloc_vid(grp, vlan_id);
	if (err < 0)
		goto out_uninit_applicant;

	err = register_netdevice(dev);
	if (err < 0)
		goto out_uninit_applicant;

	/* Account for reference in struct vlan_dev_info */
	dev_hold(real_dev);

	netif_stacked_transfer_operstate(real_dev, dev);
	linkwatch_fire_event(dev); /* _MUST_ call rfc2863_policy() */

	/* So, got the sucker initialized, now lets place
	 * it into our local structure.
	 */
	vlan_group_set_device(grp, vlan_id, dev);
	grp->nr_vlans++;

	if (ngrp && real_dev->features & NETIF_F_HW_VLAN_RX)
		ops->ndo_vlan_rx_register(real_dev, ngrp);
	if (real_dev->features & NETIF_F_HW_VLAN_FILTER)
		ops->ndo_vlan_rx_add_vid(real_dev, vlan_id);

	return 0;

out_uninit_applicant:
	if (ngrp)
		vlan_gvrp_uninit_applicant(real_dev);
out_free_group:
	if (ngrp) {
		hlist_del_rcu(&ngrp->hlist);
		/* Free the group, after all cpu's are done. */
		call_rcu(&ngrp->rcu, vlan_rcu_free);
	}
	return err;
}