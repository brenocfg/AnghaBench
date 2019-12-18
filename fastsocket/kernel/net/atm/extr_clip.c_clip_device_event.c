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
struct net_device {scalar_t__ type; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ATM ; 
#define  NETDEV_CHANGE 131 
#define  NETDEV_CHANGEMTU 130 
#define  NETDEV_GOING_DOWN 129 
 unsigned long NETDEV_UNREGISTER ; 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 TYPE_1__* PRIV (struct net_device*) ; 
 int /*<<< orphan*/  act_change ; 
 int /*<<< orphan*/  act_down ; 
 int /*<<< orphan*/  act_up ; 
 int /*<<< orphan*/  clip_netdev_ops ; 
 int /*<<< orphan*/  clip_tbl ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  neigh_ifdown (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  to_atmarpd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clip_device_event(struct notifier_block *this, unsigned long event,
			     void *arg)
{
	struct net_device *dev = arg;

	if (!net_eq(dev_net(dev), &init_net))
		return NOTIFY_DONE;

	if (event == NETDEV_UNREGISTER) {
		neigh_ifdown(&clip_tbl, dev);
		return NOTIFY_DONE;
	}

	/* ignore non-CLIP devices */
	if (dev->type != ARPHRD_ATM || dev->netdev_ops != &clip_netdev_ops)
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		pr_debug("clip_device_event NETDEV_UP\n");
		to_atmarpd(act_up, PRIV(dev)->number, 0);
		break;
	case NETDEV_GOING_DOWN:
		pr_debug("clip_device_event NETDEV_DOWN\n");
		to_atmarpd(act_down, PRIV(dev)->number, 0);
		break;
	case NETDEV_CHANGE:
	case NETDEV_CHANGEMTU:
		pr_debug("clip_device_event NETDEV_CHANGE*\n");
		to_atmarpd(act_change, PRIV(dev)->number, 0);
		break;
	}
	return NOTIFY_DONE;
}