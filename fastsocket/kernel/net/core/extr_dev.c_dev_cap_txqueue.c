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
typedef  scalar_t__ u16 ;
struct net_device {scalar_t__ real_num_tx_queues; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ net_ratelimit () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline u16 dev_cap_txqueue(struct net_device *dev, u16 queue_index)
{
	if (unlikely(queue_index >= dev->real_num_tx_queues)) {
		if (net_ratelimit()) {
			WARN(1, "%s selects TX queue %d, but "
			     "real number of TX queues is %d\n",
			     dev->name, queue_index,
			     dev->real_num_tx_queues);
		}
		return 0;
	}
	return queue_index;
}