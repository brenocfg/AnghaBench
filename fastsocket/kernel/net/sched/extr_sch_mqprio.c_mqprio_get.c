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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {unsigned int num_tx_queues; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 unsigned int TC_H_MIN (int /*<<< orphan*/ ) ; 
 unsigned int netdev_get_num_tc (struct net_device*) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 

__attribute__((used)) static unsigned long mqprio_get(struct Qdisc *sch, u32 classid)
{
	struct net_device *dev = qdisc_dev(sch);
	unsigned int ntx = TC_H_MIN(classid);

	if (ntx > dev->num_tx_queues + netdev_get_num_tc(dev))
		return 0;
	return ntx;
}