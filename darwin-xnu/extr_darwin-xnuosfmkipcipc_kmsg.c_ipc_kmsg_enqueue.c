#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ipc_kmsg_t ;
typedef  TYPE_2__* ipc_kmsg_queue_t ;
struct TYPE_7__ {TYPE_1__* ikmq_base; } ;
struct TYPE_6__ {struct TYPE_6__* ikm_next; struct TYPE_6__* ikm_prev; } ;

/* Variables and functions */
 TYPE_1__* IKM_NULL ; 

void
ipc_kmsg_enqueue(
	ipc_kmsg_queue_t	queue,
	ipc_kmsg_t		kmsg)
{
	ipc_kmsg_t first = queue->ikmq_base;
	ipc_kmsg_t last;

	if (first == IKM_NULL) {
		queue->ikmq_base = kmsg;
		kmsg->ikm_next = kmsg;
		kmsg->ikm_prev = kmsg;
	} else {
		last = first->ikm_prev;
		kmsg->ikm_next = first;
		kmsg->ikm_prev = last;
		first->ikm_prev = kmsg;
		last->ikm_next = kmsg;
	}
}