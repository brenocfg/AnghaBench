#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vport_parms {int /*<<< orphan*/  name; } ;
struct vport {int /*<<< orphan*/  dp; } ;
struct netdev_vport {TYPE_1__* dev; } ;
struct TYPE_5__ {int flags; scalar_t__ type; int /*<<< orphan*/  priv_flags; struct vport* ax25_ptr; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 struct vport* ERR_PTR (int) ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  IFF_OVS_DATAPATH ; 
 scalar_t__ IS_ERR (struct vport*) ; 
 int PTR_ERR (struct vport*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* dev_get_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_promiscuity (TYPE_1__*,int) ; 
 struct netdev_vport* netdev_vport_priv (struct vport*) ; 
 int /*<<< orphan*/  nr_bridges ; 
 int /*<<< orphan*/  openvswitch_handle_frame_hook ; 
 int /*<<< orphan*/  ovs_dp_get_net (int /*<<< orphan*/ ) ; 
 scalar_t__ ovs_is_internal_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  ovs_netdev_frame_hook ; 
 int /*<<< orphan*/  ovs_netdev_vport_ops ; 
 struct vport* ovs_vport_alloc (int,int /*<<< orphan*/ *,struct vport_parms const*) ; 
 int /*<<< orphan*/  ovs_vport_free (struct vport*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static struct vport *netdev_create(const struct vport_parms *parms)
{
	struct vport *vport;
	struct netdev_vport *netdev_vport;
	int err;

	vport = ovs_vport_alloc(sizeof(struct netdev_vport),
				&ovs_netdev_vport_ops, parms);
	if (IS_ERR(vport)) {
		err = PTR_ERR(vport);
		goto error;
	}

	netdev_vport = netdev_vport_priv(vport);

	netdev_vport->dev = dev_get_by_name(ovs_dp_get_net(vport->dp), parms->name);
	if (!netdev_vport->dev) {
		err = -ENODEV;
		goto error_free_vport;
	}

	if (netdev_vport->dev->flags & IFF_LOOPBACK ||
	    netdev_vport->dev->type != ARPHRD_ETHER ||
	    ovs_is_internal_dev(netdev_vport->dev)) {
		err = -EINVAL;
		goto error_put;
	}

	err = -EBUSY;
	rtnl_lock();
	if (netdev_vport->dev->ax25_ptr)
		goto error_unlock;

	netdev_vport->dev->ax25_ptr = vport;

	atomic_inc(&nr_bridges);
	openvswitch_handle_frame_hook = ovs_netdev_frame_hook;

	dev_set_promiscuity(netdev_vport->dev, 1);
	netdev_vport->dev->priv_flags |= IFF_OVS_DATAPATH;
	rtnl_unlock();

	return vport;

error_unlock:
	rtnl_unlock();
error_put:
	dev_put(netdev_vport->dev);
error_free_vport:
	ovs_vport_free(vport);
error:
	return ERR_PTR(err);
}