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
struct net_device {struct ec_device* ec_ptr; } ;
struct ec_device {size_t net; } ;

/* Variables and functions */
#define  NETDEV_UNREGISTER 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree (struct ec_device*) ; 
 struct net_device** net2dev_map ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int econet_notifier(struct notifier_block *this, unsigned long msg, void *data)
{
	struct net_device *dev = (struct net_device *)data;
	struct ec_device *edev;

	if (!net_eq(dev_net(dev), &init_net))
		return NOTIFY_DONE;

	switch (msg) {
	case NETDEV_UNREGISTER:
		/* A device has gone down - kill any data we hold for it. */
		edev = dev->ec_ptr;
		if (edev)
		{
			if (net2dev_map[0] == dev)
				net2dev_map[0] = NULL;
			net2dev_map[edev->net] = NULL;
			kfree(edev);
			dev->ec_ptr = NULL;
		}
		break;
	}

	return NOTIFY_DONE;
}