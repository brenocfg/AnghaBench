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
struct rpc_xprt {unsigned int connect_cookie; int /*<<< orphan*/  transport_lock; int /*<<< orphan*/  task_cleanup; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  XPRT_CLOSE_WAIT ; 
 int /*<<< orphan*/  XPRT_CLOSING ; 
 int /*<<< orphan*/  XPRT_LOCKED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpciod_workqueue ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_connected (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_wake_pending_tasks (struct rpc_xprt*,int /*<<< orphan*/ ) ; 

void xprt_conditional_disconnect(struct rpc_xprt *xprt, unsigned int cookie)
{
	/* Don't race with the test_bit() in xprt_clear_locked() */
	spin_lock_bh(&xprt->transport_lock);
	if (cookie != xprt->connect_cookie)
		goto out;
	if (test_bit(XPRT_CLOSING, &xprt->state) || !xprt_connected(xprt))
		goto out;
	set_bit(XPRT_CLOSE_WAIT, &xprt->state);
	/* Try to schedule an autoclose RPC call */
	if (test_and_set_bit(XPRT_LOCKED, &xprt->state) == 0)
		queue_work(rpciod_workqueue, &xprt->task_cleanup);
	xprt_wake_pending_tasks(xprt, -EAGAIN);
out:
	spin_unlock_bh(&xprt->transport_lock);
}