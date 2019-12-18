#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vport_parms {int /*<<< orphan*/  name; } ;
struct vport {scalar_t__ port_no; int /*<<< orphan*/  dp; } ;
struct netdev_vport {TYPE_1__* dev; } ;
struct internal_dev {struct vport* vport; } ;
struct TYPE_8__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct vport* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct vport*) ; 
 int /*<<< orphan*/  NETIF_F_NETNS_LOCAL ; 
 scalar_t__ OVSP_LOCAL ; 
 int PTR_ERR (struct vport*) ; 
 TYPE_1__* alloc_netdev (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_promiscuity (TYPE_1__*,int) ; 
 int /*<<< orphan*/  do_setup ; 
 int /*<<< orphan*/  free_netdev (TYPE_1__*) ; 
 struct internal_dev* internal_dev_priv (TYPE_1__*) ; 
 struct netdev_vport* netdev_vport_priv (struct vport*) ; 
 int /*<<< orphan*/  netif_start_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  ovs_dp_get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_internal_vport_ops ; 
 struct vport* ovs_vport_alloc (int,int /*<<< orphan*/ *,struct vport_parms const*) ; 
 int /*<<< orphan*/  ovs_vport_free (struct vport*) ; 
 int register_netdevice (TYPE_1__*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static struct vport *internal_dev_create(const struct vport_parms *parms)
{
	struct vport *vport;
	struct netdev_vport *netdev_vport;
	struct internal_dev *internal_dev;
	int err;

	vport = ovs_vport_alloc(sizeof(struct netdev_vport),
				&ovs_internal_vport_ops, parms);
	if (IS_ERR(vport)) {
		err = PTR_ERR(vport);
		goto error;
	}

	netdev_vport = netdev_vport_priv(vport);

	netdev_vport->dev = alloc_netdev(sizeof(struct internal_dev),
					 parms->name, do_setup);
	if (!netdev_vport->dev) {
		err = -ENOMEM;
		goto error_free_vport;
	}

	dev_net_set(netdev_vport->dev, ovs_dp_get_net(vport->dp));
	internal_dev = internal_dev_priv(netdev_vport->dev);
	internal_dev->vport = vport;

	/* Restrict bridge port to current netns. */
	if (vport->port_no == OVSP_LOCAL)
		netdev_vport->dev->features |= NETIF_F_NETNS_LOCAL;

	rtnl_lock();
	err = register_netdevice(netdev_vport->dev);
	if (err)
		goto error_free_netdev;

	dev_set_promiscuity(netdev_vport->dev, 1);
	rtnl_unlock();
	netif_start_queue(netdev_vport->dev);

	return vport;

error_free_netdev:
	rtnl_unlock();
	free_netdev(netdev_vport->dev);
error_free_vport:
	ovs_vport_free(vport);
error:
	return ERR_PTR(err);
}