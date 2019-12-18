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
struct vio_dev {size_t unit_address; } ;
struct veth_port {int lpar_map; int /*<<< orphan*/  kobject; } ;
struct veth_lpar_connection {int /*<<< orphan*/  kobject; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int HVMAXARCHITECTEDLPS ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct veth_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 struct veth_lpar_connection** veth_cnx ; 
 struct net_device** veth_dev ; 

__attribute__((used)) static int veth_remove(struct vio_dev *vdev)
{
	struct veth_lpar_connection *cnx;
	struct net_device *dev;
	struct veth_port *port;
	int i;

	dev = veth_dev[vdev->unit_address];

	if (! dev)
		return 0;

	port = netdev_priv(dev);

	for (i = 0; i < HVMAXARCHITECTEDLPS; i++) {
		cnx = veth_cnx[i];

		if (cnx && (port->lpar_map & (1 << i))) {
			/* Drop our reference to connections on our VLAN */
			kobject_put(&cnx->kobject);
		}
	}

	veth_dev[vdev->unit_address] = NULL;
	kobject_del(&port->kobject);
	kobject_put(&port->kobject);
	unregister_netdev(dev);
	free_netdev(dev);

	return 0;
}