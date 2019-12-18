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
struct waitq_set {int dummy; } ;
struct waitq {int dummy; } ;
typedef  TYPE_1__* ipc_mqueue_t ;
struct TYPE_2__ {int /*<<< orphan*/  imq_messages; } ;

/* Variables and functions */
 int WQ_ITERATE_BREAK_KEEP_LOCKED ; 
 int WQ_ITERATE_INVALIDATE_CONTINUE ; 
 scalar_t__ ipc_kmsg_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mqueue_process_prepost_receive(void *ctx, struct waitq *waitq,
					  struct waitq_set *wqset)
{
	ipc_mqueue_t     port_mq, *pmq_ptr;

	(void)wqset;
	port_mq = (ipc_mqueue_t)waitq;

	/*
	 * If there are no messages on this queue, skip it and remove
	 * it from the prepost list
	 */
	if (ipc_kmsg_queue_empty(&port_mq->imq_messages))
		return WQ_ITERATE_INVALIDATE_CONTINUE;

	/*
	 * There are messages waiting on this port.
	 * Instruct the prepost iteration logic to break, but keep the
	 * waitq locked.
	 */
	pmq_ptr = (ipc_mqueue_t *)ctx;
	if (pmq_ptr)
		*pmq_ptr = port_mq;
	return WQ_ITERATE_BREAK_KEEP_LOCKED;
}