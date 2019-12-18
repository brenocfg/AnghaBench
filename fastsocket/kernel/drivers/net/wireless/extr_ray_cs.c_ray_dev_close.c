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
struct pcmcia_device {int /*<<< orphan*/  open; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct pcmcia_device* finder; } ;
typedef  TYPE_1__ ray_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int ray_dev_close(struct net_device *dev)
{
	ray_dev_t *local = netdev_priv(dev);
	struct pcmcia_device *link;
	link = local->finder;

	DEBUG(1, "ray_dev_close('%s')\n", dev->name);

	link->open--;
	netif_stop_queue(dev);

	/* In here, we should stop the hardware (stop card from beeing active)
	 * and set local->card_status to CARD_AWAITING_PARAM, so that while the
	 * card is closed we can chage its configuration.
	 * Probably also need a COR reset to get sane state - Jean II */

	return 0;
}