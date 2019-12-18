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
struct net_device {int priv_flags; int flags; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int EPERM ; 
 int IFF_EBRIDGE ; 
 int IFF_UP ; 
 struct net_device* __dev_get_by_name (struct net*,char const*) ; 
 int /*<<< orphan*/  del_br (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int br_del_bridge(struct net *net, const char *name)
{
	struct net_device *dev;
	int ret = 0;

	rtnl_lock();
	dev = __dev_get_by_name(net, name);
	if (dev == NULL)
		ret =  -ENXIO; 	/* Could not find device */

	else if (!(dev->priv_flags & IFF_EBRIDGE)) {
		/* Attempt to delete non bridge device! */
		ret = -EPERM;
	}

	else if (dev->flags & IFF_UP) {
		/* Not shutdown yet. */
		ret = -EBUSY;
	}

	else
		del_br(netdev_priv(dev));

	rtnl_unlock();
	return ret;
}