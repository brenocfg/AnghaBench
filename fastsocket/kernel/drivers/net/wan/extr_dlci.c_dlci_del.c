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
struct net_device {int dummy; } ;
struct frad_local {int (* deassoc ) (struct net_device*,struct net_device*) ;} ;
struct dlci_local {int /*<<< orphan*/  list; struct net_device* slave; } ;
struct dlci_add {int /*<<< orphan*/  devname; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 struct net_device* __dev_get_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 void* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int stub1 (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static int dlci_del(struct dlci_add *dlci)
{
	struct dlci_local	*dlp;
	struct frad_local	*flp;
	struct net_device	*master, *slave;
	int			err;

	/* validate slave device */
	master = __dev_get_by_name(&init_net, dlci->devname);
	if (!master)
		return(-ENODEV);

	if (netif_running(master)) {
		return(-EBUSY);
	}

	dlp = netdev_priv(master);
	slave = dlp->slave;
	flp = netdev_priv(slave);

	rtnl_lock();
	err = (*flp->deassoc)(slave, master);
	if (!err) {
		list_del(&dlp->list);

		unregister_netdevice(master);

		dev_put(slave);
	}
	rtnl_unlock();

	return(err);
}