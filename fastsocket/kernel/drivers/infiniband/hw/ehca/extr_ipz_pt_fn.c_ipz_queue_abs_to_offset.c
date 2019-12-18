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
typedef  scalar_t__ u64 ;
struct ipz_queue {int queue_length; int pagesize; int /*<<< orphan*/ * queue_pages; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  virt_to_abs (int /*<<< orphan*/ ) ; 

int ipz_queue_abs_to_offset(struct ipz_queue *queue, u64 addr, u64 *q_offset)
{
	int i;
	for (i = 0; i < queue->queue_length / queue->pagesize; i++) {
		u64 page = (u64)virt_to_abs(queue->queue_pages[i]);
		if (addr >= page && addr < page + queue->pagesize) {
			*q_offset = addr - page + i * queue->pagesize;
			return 0;
		}
	}
	return -EINVAL;
}