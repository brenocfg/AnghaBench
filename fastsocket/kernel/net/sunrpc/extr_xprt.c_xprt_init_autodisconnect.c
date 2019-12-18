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
struct rpc_xprt {int /*<<< orphan*/  transport_lock; int /*<<< orphan*/  task_cleanup; int /*<<< orphan*/  state; int /*<<< orphan*/  recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_CONNECTION_CLOSE ; 
 int /*<<< orphan*/  XPRT_LOCKED ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpciod_workqueue ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xprt_init_autodisconnect(unsigned long data)
{
	struct rpc_xprt *xprt = (struct rpc_xprt *)data;

	spin_lock(&xprt->transport_lock);
	if (!list_empty(&xprt->recv))
		goto out_abort;
	if (test_and_set_bit(XPRT_LOCKED, &xprt->state))
		goto out_abort;
	spin_unlock(&xprt->transport_lock);
	set_bit(XPRT_CONNECTION_CLOSE, &xprt->state);
	queue_work(rpciod_workqueue, &xprt->task_cleanup);
	return;
out_abort:
	spin_unlock(&xprt->transport_lock);
}