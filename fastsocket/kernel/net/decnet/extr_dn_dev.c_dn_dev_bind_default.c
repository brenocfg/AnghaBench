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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {struct net_device* loopback_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_base_lock ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct net_device* dn_dev_get_default () ; 
 int dn_dev_get_first (struct net_device*,int /*<<< orphan*/ *) ; 
 TYPE_1__ init_net ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int dn_dev_bind_default(__le16 *addr)
{
	struct net_device *dev;
	int rv;
	dev = dn_dev_get_default();
last_chance:
	if (dev) {
		read_lock(&dev_base_lock);
		rv = dn_dev_get_first(dev, addr);
		read_unlock(&dev_base_lock);
		dev_put(dev);
		if (rv == 0 || dev == init_net.loopback_dev)
			return rv;
	}
	dev = init_net.loopback_dev;
	dev_hold(dev);
	goto last_chance;
}