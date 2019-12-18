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
#define  NETDEV_CHANGEADDR 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  arp_tbl ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  neigh_changeaddr (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  rt_cache_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arp_netdev_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *dev = ptr;

	switch (event) {
	case NETDEV_CHANGEADDR:
		neigh_changeaddr(&arp_tbl, dev);
		rt_cache_flush(dev_net(dev), 0);
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}