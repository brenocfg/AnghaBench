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
struct device {int /*<<< orphan*/  kobj; } ;
struct net_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dev_net (struct net_device*) ; 
 int /*<<< orphan*/  device_del (struct device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_queue_kobjects (struct net_device*) ; 

void netdev_unregister_kobject(struct net_device * net)
{
	struct device *dev = &(net->dev);

	kobject_get(&dev->kobj);

	if (dev_net(net) != &init_net)
		return;

	remove_queue_kobjects(net);

	device_del(dev);
}