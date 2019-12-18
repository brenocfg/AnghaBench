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
struct net_device {int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  br_port; int /*<<< orphan*/  name; } ;
struct net_bridge_port {int /*<<< orphan*/  rcu; int /*<<< orphan*/  kobj; int /*<<< orphan*/  list; struct net_device* dev; struct net_bridge* br; } ;
struct net_bridge {int /*<<< orphan*/  lock; int /*<<< orphan*/  ifobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_BRIDGE_PORT ; 
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 int /*<<< orphan*/  RTM_DELLINK ; 
 int /*<<< orphan*/  br_del_vlans_from_port (struct net_bridge*,struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_fdb_delete_by_port (struct net_bridge*,struct net_bridge_port*,int) ; 
 int /*<<< orphan*/  br_ifinfo_notify (int /*<<< orphan*/ ,struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_multicast_del_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_netpoll_disable (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_stp_disable_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_nbp_rcu ; 
 int /*<<< orphan*/  dev_set_promiscuity (struct net_device*,int) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void del_nbp(struct net_bridge_port *p)
{
	struct net_bridge *br = p->br;
	struct net_device *dev = p->dev;

	sysfs_remove_link(br->ifobj, dev->name);

	dev_set_promiscuity(dev, -1);

	br_del_vlans_from_port(br, p);

	spin_lock_bh(&br->lock);
	br_stp_disable_port(p);
	spin_unlock_bh(&br->lock);

	br_ifinfo_notify(RTM_DELLINK, p);

	br_fdb_delete_by_port(br, p, 1);

	list_del_rcu(&p->list);

	rcu_assign_pointer(dev->br_port, NULL);

	dev->priv_flags &= ~IFF_BRIDGE_PORT;

	br_multicast_del_port(p);

	kobject_uevent(&p->kobj, KOBJ_REMOVE);
	kobject_del(&p->kobj);

	br_netpoll_disable(p);

	call_rcu(&p->rcu, destroy_nbp_rcu);
}