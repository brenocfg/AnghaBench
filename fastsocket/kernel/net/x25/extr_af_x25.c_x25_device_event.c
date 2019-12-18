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
struct x25_neigh {int dummy; } ;
struct notifier_block {int dummy; } ;
struct net_device {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 scalar_t__ ARPHRD_X25 ; 
#define  NETDEV_DOWN 130 
#define  NETDEV_GOING_DOWN 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct x25_neigh* x25_get_neigh (struct net_device*) ; 
 int /*<<< orphan*/  x25_kill_by_device (struct net_device*) ; 
 int /*<<< orphan*/  x25_link_device_down (struct net_device*) ; 
 int /*<<< orphan*/  x25_link_device_up (struct net_device*) ; 
 int /*<<< orphan*/  x25_neigh_put (struct x25_neigh*) ; 
 int /*<<< orphan*/  x25_route_device_down (struct net_device*) ; 
 int /*<<< orphan*/  x25_terminate_link (struct x25_neigh*) ; 

__attribute__((used)) static int x25_device_event(struct notifier_block *this, unsigned long event,
			    void *ptr)
{
	struct net_device *dev = ptr;
	struct x25_neigh *nb;

	if (!net_eq(dev_net(dev), &init_net))
		return NOTIFY_DONE;

	if (dev->type == ARPHRD_X25
#if defined(CONFIG_LLC) || defined(CONFIG_LLC_MODULE)
	 || dev->type == ARPHRD_ETHER
#endif
	 ) {
		switch (event) {
			case NETDEV_UP:
				x25_link_device_up(dev);
				break;
			case NETDEV_GOING_DOWN:
				nb = x25_get_neigh(dev);
				if (nb) {
					x25_terminate_link(nb);
					x25_neigh_put(nb);
				}
				break;
			case NETDEV_DOWN:
				x25_kill_by_device(dev);
				x25_route_device_down(dev);
				x25_link_device_down(dev);
				break;
		}
	}

	return NOTIFY_DONE;
}