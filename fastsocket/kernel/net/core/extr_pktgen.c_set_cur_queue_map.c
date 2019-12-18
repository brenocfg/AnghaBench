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
struct pktgen_dev {int flags; scalar_t__ cur_queue_map; scalar_t__ queue_map_min; scalar_t__ queue_map_max; TYPE_1__* odev; } ;
typedef  scalar_t__ __u16 ;
struct TYPE_2__ {int real_num_tx_queues; } ;

/* Variables and functions */
 int F_QUEUE_MAP_CPU ; 
 int F_QUEUE_MAP_RND ; 
 int random32 () ; 
 scalar_t__ smp_processor_id () ; 

__attribute__((used)) static void set_cur_queue_map(struct pktgen_dev *pkt_dev)
{

	if (pkt_dev->flags & F_QUEUE_MAP_CPU)
		pkt_dev->cur_queue_map = smp_processor_id();

	else if (pkt_dev->queue_map_min <= pkt_dev->queue_map_max) {
		__u16 t;
		if (pkt_dev->flags & F_QUEUE_MAP_RND) {
			t = random32() %
				(pkt_dev->queue_map_max -
				 pkt_dev->queue_map_min + 1)
				+ pkt_dev->queue_map_min;
		} else {
			t = pkt_dev->cur_queue_map + 1;
			if (t > pkt_dev->queue_map_max)
				t = pkt_dev->queue_map_min;
		}
		pkt_dev->cur_queue_map = t;
	}
	pkt_dev->cur_queue_map  = pkt_dev->cur_queue_map % pkt_dev->odev->real_num_tx_queues;
}