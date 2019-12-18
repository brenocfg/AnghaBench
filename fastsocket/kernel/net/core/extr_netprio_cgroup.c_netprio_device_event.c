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
struct notifier_block {int dummy; } ;
struct netprio_map {int /*<<< orphan*/  rcu; } ;
struct netdev_priomap_info {int /*<<< orphan*/  priomap; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct netdev_priomap_info priomap_data; } ;

/* Variables and functions */
#define  NETDEV_UNREGISTER 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_priomap_rcu ; 
 TYPE_1__* netdev_extended (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct netprio_map* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netprio_device_event(struct notifier_block *unused,
				unsigned long event, void *ptr)
{
	struct net_device *dev = ptr;
	struct netprio_map *old;
	struct netdev_priomap_info *data;

	/*
	 * Note this is called with rtnl_lock held so we have update side
	 * protection on our rcu assignments
	 */

	switch (event) {
	case NETDEV_UNREGISTER:
		data = &netdev_extended(dev)->priomap_data;
		old = rcu_dereference(data->priomap);
		rcu_assign_pointer(data->priomap, NULL);
		if (old)
			call_rcu(&old->rcu, free_priomap_rcu);
		break;
	}
	return NOTIFY_DONE;
}