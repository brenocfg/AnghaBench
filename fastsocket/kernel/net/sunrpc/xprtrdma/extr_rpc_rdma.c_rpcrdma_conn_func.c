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
struct rpcrdma_ep {scalar_t__ rep_connected; struct rpc_xprt* rep_xprt; } ;
struct rpc_xprt {scalar_t__ connect_cookie; int /*<<< orphan*/  transport_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ xprt_test_and_clear_connected (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_test_and_set_connected (struct rpc_xprt*) ; 
 int /*<<< orphan*/  xprt_wake_pending_tasks (struct rpc_xprt*,int /*<<< orphan*/ ) ; 

void
rpcrdma_conn_func(struct rpcrdma_ep *ep)
{
	struct rpc_xprt *xprt = ep->rep_xprt;

	spin_lock_bh(&xprt->transport_lock);
	if (++xprt->connect_cookie == 0)	/* maintain a reserved value */
		++xprt->connect_cookie;
	if (ep->rep_connected > 0) {
		if (!xprt_test_and_set_connected(xprt))
			xprt_wake_pending_tasks(xprt, 0);
	} else {
		if (xprt_test_and_clear_connected(xprt))
			xprt_wake_pending_tasks(xprt, -ENOTCONN);
	}
	spin_unlock_bh(&xprt->transport_lock);
}