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
struct rpc_xprt {int dummy; } ;
struct rpc_task {scalar_t__ tk_status; int /*<<< orphan*/  tk_action; int /*<<< orphan*/  tk_pid; struct rpc_xprt* tk_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_connect_status ; 
 int /*<<< orphan*/  call_transmit ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,struct rpc_xprt*,char*) ; 
 int /*<<< orphan*/  xprt_connect (struct rpc_task*) ; 
 scalar_t__ xprt_connected (struct rpc_xprt*) ; 

__attribute__((used)) static void
call_connect(struct rpc_task *task)
{
	struct rpc_xprt *xprt = task->tk_xprt;

	dprintk("RPC: %5u call_connect xprt %p %s connected\n",
			task->tk_pid, xprt,
			(xprt_connected(xprt) ? "is" : "is not"));

	task->tk_action = call_transmit;
	if (!xprt_connected(xprt)) {
		task->tk_action = call_connect_status;
		if (task->tk_status < 0)
			return;
		xprt_connect(task);
	}
}