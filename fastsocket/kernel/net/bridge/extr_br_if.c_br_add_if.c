#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct net_device {int flags; scalar_t__ type; scalar_t__ addr_len; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/ * br_port; int /*<<< orphan*/  dev_addr; TYPE_2__ dev; TYPE_1__* netdev_ops; } ;
struct net_bridge_port {int /*<<< orphan*/  kobj; TYPE_3__* dev; int /*<<< orphan*/  list; } ;
struct net_bridge {int /*<<< orphan*/  ifobj; TYPE_5__* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  port_list; } ;
struct TYPE_10__ {int flags; } ;
struct TYPE_9__ {int ext_priv_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {scalar_t__ ndo_start_xmit; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int EBUSY ; 
 int EINVAL ; 
 int ELOOP ; 
 int EOPNOTSUPP ; 
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  IFF_BRIDGE_PORT ; 
 int IFF_DONT_BRIDGE ; 
 int IFF_LOOPBACK ; 
 int IFF_UP ; 
 scalar_t__ IS_ERR (struct net_bridge_port*) ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  NETDEV_JOIN ; 
 int PTR_ERR (struct net_bridge_port*) ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 int /*<<< orphan*/  SYSFS_BRIDGE_PORT_ATTR ; 
 int /*<<< orphan*/  br_add_vlans_to_port (struct net_bridge*,struct net_bridge_port*) ; 
 scalar_t__ br_dev_xmit ; 
 int /*<<< orphan*/  br_fdb_delete_by_port (struct net_bridge*,struct net_bridge_port*,int) ; 
 int br_fdb_insert (struct net_bridge*,struct net_bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_features_recompute (struct net_bridge*) ; 
 int /*<<< orphan*/  br_ifinfo_notify (int /*<<< orphan*/ ,struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_min_mtu (struct net_bridge*) ; 
 int br_netpoll_enable (struct net_bridge_port*) ; 
 scalar_t__ br_netpoll_info (struct net_bridge*) ; 
 int /*<<< orphan*/  br_stp_enable_port (struct net_bridge_port*) ; 
 int /*<<< orphan*/  br_stp_recalculate_bridge_id (struct net_bridge*) ; 
 int br_sysfs_addif (struct net_bridge_port*) ; 
 int /*<<< orphan*/  brport_ktype ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  dev_disable_lro (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dev_set_mtu (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int dev_set_promiscuity (struct net_device*,int) ; 
 int /*<<< orphan*/  kfree (struct net_bridge_port*) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* netdev_extended (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 struct net_bridge_port* new_nbp (struct net_bridge*,struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ *,struct net_bridge_port*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int br_add_if(struct net_bridge *br, struct net_device *dev)
{
	struct net_bridge_port *p;
	int err = 0;

	/* Don't allow bridging non-ethernet like devices */
	if ((dev->flags & IFF_LOOPBACK) ||
	    dev->type != ARPHRD_ETHER || dev->addr_len != ETH_ALEN)
		return -EINVAL;

	/* No bridging of bridges */
	if (dev->netdev_ops->ndo_start_xmit == br_dev_xmit)
		return -ELOOP;

	/* Device is already being bridged */
	if (dev->br_port != NULL)
		return -EBUSY;

	/* No bridging devices that dislike that (e.g. wireless) */
	if (netdev_extended(dev)->ext_priv_flags & IFF_DONT_BRIDGE)
		return -EOPNOTSUPP;

	p = new_nbp(br, dev);
	if (IS_ERR(p))
		return PTR_ERR(p);

	err = dev_set_promiscuity(dev, 1);
	if (err)
		goto put_back;

	call_netdevice_notifiers(NETDEV_JOIN, dev);

	err = kobject_init_and_add(&p->kobj, &brport_ktype, &(dev->dev.kobj),
				   SYSFS_BRIDGE_PORT_ATTR);
	if (err)
		goto err0;

	err = br_fdb_insert(br, p, dev->dev_addr);
	if (err)
		goto err1;

	err = br_sysfs_addif(p);
	if (err)
		goto err2;

	if (br_netpoll_info(br) && ((err = br_netpoll_enable(p))))
		goto err3;

	rcu_assign_pointer(dev->br_port, p);

	dev_disable_lro(dev);

	dev->priv_flags |= IFF_BRIDGE_PORT;

	list_add_rcu(&p->list, &br->port_list);

	br_add_vlans_to_port(br, p);

	br_features_recompute(br);

	spin_lock_bh(&br->lock);
	br_stp_recalculate_bridge_id(br);

	if ((dev->flags & IFF_UP) && netif_carrier_ok(dev) &&
	    (br->dev->flags & IFF_UP))
		br_stp_enable_port(p);
	spin_unlock_bh(&br->lock);

	br_ifinfo_notify(RTM_NEWLINK, p);

	dev_set_mtu(br->dev, br_min_mtu(br));

	kobject_uevent(&p->kobj, KOBJ_ADD);

	return 0;
err3:
	sysfs_remove_link(br->ifobj, p->dev->name);
err2:
	br_fdb_delete_by_port(br, p, 1);
err1:
	kobject_put(&p->kobj);
	p = NULL; /* kobject_put frees */
err0:
	dev_set_promiscuity(dev, -1);
put_back:
	dev_put(dev);
	kfree(p);
	return err;
}