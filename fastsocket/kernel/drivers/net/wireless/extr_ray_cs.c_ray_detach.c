#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_device {scalar_t__ dev_node; struct net_device* priv; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  timer; } ;
typedef  TYPE_1__ ray_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,...) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ray_release (struct pcmcia_device*) ; 
 int /*<<< orphan*/ * this_device ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void ray_detach(struct pcmcia_device *link)
{
	struct net_device *dev;
	ray_dev_t *local;

	DEBUG(1, "ray_detach(0x%p)\n", link);

	this_device = NULL;
	dev = link->priv;

	ray_release(link);

	local = netdev_priv(dev);
	del_timer(&local->timer);

	if (link->priv) {
		if (link->dev_node)
			unregister_netdev(dev);
		free_netdev(dev);
	}
	DEBUG(2, "ray_cs ray_detach ending\n");
}