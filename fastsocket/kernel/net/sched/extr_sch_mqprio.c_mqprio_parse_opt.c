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
struct tc_mqprio_qopt {int num_tc; int* prio_tc_map; unsigned int* offset; unsigned int* count; scalar_t__ hw; } ;
struct net_device {unsigned int real_num_tx_queues; } ;

/* Variables and functions */
 int EINVAL ; 
 int TC_BITMASK ; 
 int TC_MAX_QUEUE ; 

__attribute__((used)) static int mqprio_parse_opt(struct net_device *dev, struct tc_mqprio_qopt *qopt)
{
	int i, j;

	/* Verify num_tc is not out of max range */
	if (qopt->num_tc > TC_MAX_QUEUE)
		return -EINVAL;

	/* Verify priority mapping uses valid tcs */
	for (i = 0; i < TC_BITMASK + 1; i++) {
		if (qopt->prio_tc_map[i] >= qopt->num_tc)
			return -EINVAL;
	}

	/* net_device does not support requested operation */
	if (qopt->hw) {
		/*
		 * RHEL6: Can't backport ndo_setup_tc() therefore we do not support
		 * strict hardware mode.
		 */
		return -EINVAL;
	}

	for (i = 0; i < qopt->num_tc; i++) {
		unsigned int last = qopt->offset[i] + qopt->count[i];

		/* Verify the queue count is in tx range being equal to the
		 * real_num_tx_queues indicates the last queue is in use.
		 */
		if (qopt->offset[i] >= dev->real_num_tx_queues ||
		    !qopt->count[i] ||
		    last > dev->real_num_tx_queues)
			return -EINVAL;

		/* Verify that the offset and counts do not overlap */
		for (j = i + 1; j < qopt->num_tc; j++) {
			if (last > qopt->offset[j])
				return -EINVAL;
		}
	}

	return 0;
}