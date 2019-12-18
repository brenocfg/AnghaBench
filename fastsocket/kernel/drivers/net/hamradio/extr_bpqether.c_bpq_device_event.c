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
#define  NETDEV_DOWN 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  bpq_free_device (struct net_device*) ; 
 struct net_device* bpq_get_ax25_dev (struct net_device*) ; 
 int /*<<< orphan*/  bpq_new_device (struct net_device*) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_is_ethdev (struct net_device*) ; 
 int /*<<< orphan*/ * dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 

__attribute__((used)) static int bpq_device_event(struct notifier_block *this,unsigned long event, void *ptr)
{
	struct net_device *dev = (struct net_device *)ptr;

	if (dev_net(dev) != &init_net)
		return NOTIFY_DONE;

	if (!dev_is_ethdev(dev))
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:		/* new ethernet device -> new BPQ interface */
		if (bpq_get_ax25_dev(dev) == NULL)
			bpq_new_device(dev);
		break;

	case NETDEV_DOWN:	/* ethernet device closed -> close BPQ interface */
		if ((dev = bpq_get_ax25_dev(dev)) != NULL)
			dev_close(dev);
		break;

	case NETDEV_UNREGISTER:	/* ethernet device removed -> free BPQ interface */
		if ((dev = bpq_get_ax25_dev(dev)) != NULL)
			bpq_free_device(dev);
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}