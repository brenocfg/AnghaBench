#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct net_device {int flags; TYPE_3__ dev; struct iw_handler_def* wireless_handlers; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; struct lbs_private* ml_priv; } ;
struct lbs_private {TYPE_2__* dev; struct net_device* mesh_dev; } ;
struct iw_handler_def {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_5__ {TYPE_1__ dev; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  LBS_DEB_MESH ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ ) ; 
 struct net_device* alloc_netdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_setup ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_deb_mesh (char*) ; 
 int /*<<< orphan*/  lbs_ethtool_ops ; 
 int /*<<< orphan*/  lbs_mesh_attr_group ; 
 int /*<<< orphan*/  lbs_persist_config_init (struct net_device*) ; 
 int /*<<< orphan*/  lbs_pr_err (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mesh_handler_def ; 
 int /*<<< orphan*/  mesh_netdev_ops ; 
 int register_netdev (struct net_device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int lbs_add_mesh(struct lbs_private *priv)
{
	struct net_device *mesh_dev = NULL;
	int ret = 0;

	lbs_deb_enter(LBS_DEB_MESH);

	/* Allocate a virtual mesh device */
	if (!(mesh_dev = alloc_netdev(0, "msh%d", ether_setup))) {
		lbs_deb_mesh("init mshX device failed\n");
		ret = -ENOMEM;
		goto done;
	}
	mesh_dev->ml_priv = priv;
	priv->mesh_dev = mesh_dev;

	mesh_dev->netdev_ops = &mesh_netdev_ops;
	mesh_dev->ethtool_ops = &lbs_ethtool_ops;
	memcpy(mesh_dev->dev_addr, priv->dev->dev_addr,
			sizeof(priv->dev->dev_addr));

	SET_NETDEV_DEV(priv->mesh_dev, priv->dev->dev.parent);

#ifdef	WIRELESS_EXT
	mesh_dev->wireless_handlers = (struct iw_handler_def *)&mesh_handler_def;
#endif
	mesh_dev->flags |= IFF_BROADCAST | IFF_MULTICAST;
	/* Register virtual mesh interface */
	ret = register_netdev(mesh_dev);
	if (ret) {
		lbs_pr_err("cannot register mshX virtual interface\n");
		goto err_free;
	}

	ret = sysfs_create_group(&(mesh_dev->dev.kobj), &lbs_mesh_attr_group);
	if (ret)
		goto err_unregister;

	lbs_persist_config_init(mesh_dev);

	/* Everything successful */
	ret = 0;
	goto done;

err_unregister:
	unregister_netdev(mesh_dev);

err_free:
	free_netdev(mesh_dev);

done:
	lbs_deb_leave_args(LBS_DEB_MESH, "ret %d", ret);
	return ret;
}