#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* rpc_proc; } ;
struct rpc_task {int /*<<< orphan*/  tk_action; TYPE_2__ tk_msg; int /*<<< orphan*/  tk_pid; struct rpc_clnt* tk_client; } ;
struct rpc_clnt {TYPE_3__* cl_stats; int /*<<< orphan*/  cl_vers; int /*<<< orphan*/  cl_protname; } ;
struct TYPE_6__ {int /*<<< orphan*/  rpccnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_count; } ;

/* Variables and functions */
 scalar_t__ RPC_IS_ASYNC (struct rpc_task*) ; 
 int /*<<< orphan*/  call_reserve ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rpc_proc_name (struct rpc_task*) ; 

__attribute__((used)) static void
call_start(struct rpc_task *task)
{
	struct rpc_clnt	*clnt = task->tk_client;

	dprintk("RPC: %5u call_start %s%d proc %s (%s)\n", task->tk_pid,
			clnt->cl_protname, clnt->cl_vers,
			rpc_proc_name(task),
			(RPC_IS_ASYNC(task) ? "async" : "sync"));

	/* Increment call count */
	task->tk_msg.rpc_proc->p_count++;
	clnt->cl_stats->rpccnt++;
	task->tk_action = call_reserve;
}