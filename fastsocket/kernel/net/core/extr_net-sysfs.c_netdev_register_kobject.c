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
struct device {struct attribute_group const** groups; struct net_device* platform_data; int /*<<< orphan*/ * class; } ;
struct net_device {scalar_t__ ieee80211_ptr; scalar_t__ wireless_handlers; int /*<<< orphan*/  name; struct attribute_group** sysfs_groups; struct device dev; } ;
struct attribute_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_class ; 
 int /*<<< orphan*/  netstat_group ; 
 int register_queue_kobjects (struct net_device*) ; 
 int /*<<< orphan*/  wireless_group ; 

int netdev_register_kobject(struct net_device *net)
{
	struct device *dev = &(net->dev);
	const struct attribute_group **groups = net->sysfs_groups;
	int error = 0;

	dev->class = &net_class;
	dev->platform_data = net;
	dev->groups = groups;

	dev_set_name(dev, "%s", net->name);

#ifdef CONFIG_SYSFS
	*groups++ = &netstat_group;

#ifdef CONFIG_WIRELESS_EXT_SYSFS
	if (net->wireless_handlers || net->ieee80211_ptr)
		*groups++ = &wireless_group;
#endif
#endif /* CONFIG_SYSFS */

	if (dev_net(net) != &init_net)
		return 0;

	error = device_add(dev);
	if (error)
		return error;

	error = register_queue_kobjects(net);
	if (error) {
		device_del(dev);
		return error;
	}

	return error;
}