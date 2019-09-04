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
struct TYPE_7__ {scalar_t__ ikmq_base; } ;
struct TYPE_6__ {struct TYPE_6__* ikm_next; } ;

/* Variables and functions */
 scalar_t__ IKM_NULL ; 
 int /*<<< orphan*/  assert (int) ; 

ipc_kmsg_t
ipc_kmsg_queue_next(
	ipc_kmsg_queue_t	queue,
	ipc_kmsg_t		kmsg)
{
	ipc_kmsg_t next;

	assert(queue->ikmq_base != IKM_NULL);

	next = kmsg->ikm_next;
	if (queue->ikmq_base == next)
		next = IKM_NULL;

	return next;
}