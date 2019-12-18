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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct net_device {TYPE_1__ dev; } ;
struct lbs_private {struct net_device* mesh_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBS_DEB_MESH ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_mesh_attr_group ; 
 int /*<<< orphan*/  lbs_persist_config_remove (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void lbs_remove_mesh(struct lbs_private *priv)
{
	struct net_device *mesh_dev;


	mesh_dev = priv->mesh_dev;
	if (!mesh_dev)
		return;

	lbs_deb_enter(LBS_DEB_MESH);
	netif_stop_queue(mesh_dev);
	netif_carrier_off(mesh_dev);
	sysfs_remove_group(&(mesh_dev->dev.kobj), &lbs_mesh_attr_group);
	lbs_persist_config_remove(mesh_dev);
	unregister_netdev(mesh_dev);
	priv->mesh_dev = NULL;
	free_netdev(mesh_dev);
	lbs_deb_leave(LBS_DEB_MESH);
}