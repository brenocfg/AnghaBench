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
struct net {int dummy; } ;

/* Variables and functions */
#define  NETDEV_CHANGEADDR 129 
#define  NETDEV_DOWN 128 
 int NOTIFY_DONE ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  fib6_run_gc (int /*<<< orphan*/ ,struct net*,int) ; 
 int /*<<< orphan*/  nd_tbl ; 
 int /*<<< orphan*/  neigh_changeaddr (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  neigh_ifdown (int /*<<< orphan*/ *,struct net_device*) ; 

__attribute__((used)) static int ndisc_netdev_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *dev = ptr;
	struct net *net = dev_net(dev);

	switch (event) {
	case NETDEV_CHANGEADDR:
		neigh_changeaddr(&nd_tbl, dev);
		fib6_run_gc(0, net, false);
		break;
	case NETDEV_DOWN:
		neigh_ifdown(&nd_tbl, dev);
		fib6_run_gc(0, net, false);
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}