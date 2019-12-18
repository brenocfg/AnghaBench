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
typedef  int /*<<< orphan*/ * ipc_kmsg_queue_t ;
struct TYPE_2__ {int /*<<< orphan*/  imq_messages; } ;

/* Variables and functions */
 scalar_t__ IKM_NULL ; 
 int WQ_ITERATE_BREAK ; 
 int WQ_ITERATE_CONTINUE ; 
 scalar_t__ ipc_kmsg_queue_first (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mqueue_peek_iterator(void *ctx, struct waitq *waitq,
				struct waitq_set *wqset)
{
	ipc_mqueue_t port_mq = (ipc_mqueue_t)waitq;
	ipc_kmsg_queue_t kmsgs = &port_mq->imq_messages;

	(void)ctx;
	(void)wqset;

	if (ipc_kmsg_queue_first(kmsgs) != IKM_NULL)
		return WQ_ITERATE_BREAK; /* break out of the prepost iteration */

	return WQ_ITERATE_CONTINUE;
}