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
struct netdev_queue {int dummy; } ;
struct net_device {int flags; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFF_UP ; 
 int /*<<< orphan*/  dev_activate (struct net_device*) ; 
 int /*<<< orphan*/  dev_deactivate (struct net_device*) ; 
 struct Qdisc* dev_graft_qdisc (struct netdev_queue*,struct Qdisc*) ; 
 struct netdev_queue* mqprio_queue_get (struct Qdisc*,unsigned long) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 

__attribute__((used)) static int mqprio_graft(struct Qdisc *sch, unsigned long cl, struct Qdisc *new,
		    struct Qdisc **old)
{
	struct net_device *dev = qdisc_dev(sch);
	struct netdev_queue *dev_queue = mqprio_queue_get(sch, cl);

	if (!dev_queue)
		return -EINVAL;

	if (dev->flags & IFF_UP)
		dev_deactivate(dev);

	*old = dev_graft_qdisc(dev_queue, new);

	if (dev->flags & IFF_UP)
		dev_activate(dev);

	return 0;
}