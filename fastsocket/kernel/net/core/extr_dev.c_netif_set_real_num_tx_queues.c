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
struct net_device {unsigned int num_tx_queues; scalar_t__ reg_state; unsigned int real_num_tx_queues; } ;
struct TYPE_3__ {scalar_t__ num_tc; } ;
struct TYPE_4__ {TYPE_1__ qos_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 scalar_t__ NETREG_REGISTERED ; 
 scalar_t__ NETREG_UNREGISTERING ; 
 TYPE_2__* netdev_extended (struct net_device*) ; 
 int netdev_queue_update_kobjects (struct net_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  netif_setup_tc (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  qdisc_reset_all_tx_gt (struct net_device*,unsigned int) ; 

void netif_set_real_num_tx_queues(struct net_device *dev, unsigned int txq)
{
	int rc;

	if (txq < 1 || txq > dev->num_tx_queues)
		return;

	if (dev->reg_state == NETREG_REGISTERED ||
	    dev->reg_state == NETREG_UNREGISTERING) {
		ASSERT_RTNL();

		rc = netdev_queue_update_kobjects(dev, dev->real_num_tx_queues,
						  txq);
		if (netdev_extended(dev)->qos_data.num_tc)
			netif_setup_tc(dev, txq);

		if (txq < dev->real_num_tx_queues)
			qdisc_reset_all_tx_gt(dev, txq);
	}

	dev->real_num_tx_queues = txq;
}