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
struct ipz_queue {scalar_t__ queue_length; scalar_t__ qe_size; scalar_t__ current_q_offset; int toggle_state; } ;

/* Variables and functions */
 void* ipz_qeit_get (struct ipz_queue*) ; 

void *ipz_qeit_eq_get_inc(struct ipz_queue *queue)
{
	void *ret = ipz_qeit_get(queue);
	u64 last_entry_in_q = queue->queue_length - queue->qe_size;

	queue->current_q_offset += queue->qe_size;
	if (queue->current_q_offset > last_entry_in_q) {
		queue->current_q_offset = 0;
		queue->toggle_state = (~queue->toggle_state) & 1;
	}

	return ret;
}