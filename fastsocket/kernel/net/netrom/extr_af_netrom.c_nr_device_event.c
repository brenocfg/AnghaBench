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
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned long NETDEV_DOWN ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_kill_by_device (struct net_device*) ; 
 int /*<<< orphan*/  nr_rt_device_down (struct net_device*) ; 

__attribute__((used)) static int nr_device_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *dev = (struct net_device *)ptr;

	if (!net_eq(dev_net(dev), &init_net))
		return NOTIFY_DONE;

	if (event != NETDEV_DOWN)
		return NOTIFY_DONE;

	nr_kill_by_device(dev);
	nr_rt_device_down(dev);

	return NOTIFY_DONE;
}