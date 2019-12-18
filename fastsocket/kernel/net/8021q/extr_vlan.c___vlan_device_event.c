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
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  NETDEV_CHANGENAME 130 
#define  NETDEV_REGISTER 129 
#define  NETDEV_UNREGISTER 128 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_proc_add_dev (struct net_device*) ; 
 int /*<<< orphan*/  vlan_proc_rem_dev (struct net_device*) ; 

__attribute__((used)) static void __vlan_device_event(struct net_device *dev, unsigned long event)
{
	switch (event) {
	case NETDEV_CHANGENAME:
		vlan_proc_rem_dev(dev);
		if (vlan_proc_add_dev(dev) < 0)
			pr_warning("8021q: failed to change proc name for %s\n",
					dev->name);
		break;
	case NETDEV_REGISTER:
		if (vlan_proc_add_dev(dev) < 0)
			pr_warning("8021q: failed to add proc entry for %s\n",
					dev->name);
		break;
	case NETDEV_UNREGISTER:
		vlan_proc_rem_dev(dev);
		break;
	}
}