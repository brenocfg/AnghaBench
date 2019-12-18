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
struct rpc_xprt {int /*<<< orphan*/  reserve_lock; } ;
struct rpc_task {int /*<<< orphan*/  tk_status; scalar_t__ tk_timeout; int /*<<< orphan*/ * tk_rqstp; struct rpc_xprt* tk_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_alloc_slot (struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_lock_write (struct rpc_xprt*,struct rpc_task*) ; 
 int /*<<< orphan*/  xprt_release_write (struct rpc_xprt*,struct rpc_task*) ; 

void xprt_reserve(struct rpc_task *task)
{
	struct rpc_xprt	*xprt = task->tk_xprt;

	task->tk_status = 0;
	if (task->tk_rqstp != NULL)
		return;

	/* Note: grabbing the xprt_lock_write() here is not strictly needed,
	 * but ensures that we throttle new slot allocation if the transport
	 * is congested (e.g. if reconnecting or if we're out of socket
	 * write buffer space).
	 */
	task->tk_timeout = 0;
	task->tk_status = -EAGAIN;
	if (!xprt_lock_write(xprt, task))
		return;

	spin_lock(&xprt->reserve_lock);
	xprt_alloc_slot(task);
	spin_unlock(&xprt->reserve_lock);
	xprt_release_write(xprt, task);
}