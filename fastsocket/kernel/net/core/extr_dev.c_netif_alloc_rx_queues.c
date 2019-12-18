#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netdev_rx_queue {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {unsigned int num_rx_queues; struct netdev_rx_queue* _rx; } ;
struct TYPE_4__ {TYPE_1__ rps_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct netdev_rx_queue* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* netdev_extended (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

__attribute__((used)) static int netif_alloc_rx_queues(struct net_device *dev)
{
	unsigned int i, count = netdev_extended(dev)->rps_data.num_rx_queues;
	struct netdev_rx_queue *rx;

	BUG_ON(count < 1);

	rx = kcalloc(count, sizeof(struct netdev_rx_queue), GFP_KERNEL);
	if (!rx) {
		pr_err("netdev: Unable to allocate %u rx queues.\n", count);
		return -ENOMEM;
	}
	netdev_extended(dev)->rps_data._rx = rx;

	for (i = 0; i < count; i++)
		rx[i].dev = dev;
	return 0;
}