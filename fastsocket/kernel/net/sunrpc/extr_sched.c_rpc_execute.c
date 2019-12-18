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
struct rpc_task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_IS_ASYNC (struct rpc_task*) ; 
 int /*<<< orphan*/  __rpc_execute (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_make_runnable (struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_set_active (struct rpc_task*) ; 

void rpc_execute(struct rpc_task *task)
{
	rpc_set_active(task);
	rpc_make_runnable(task);
	if (!RPC_IS_ASYNC(task))
		__rpc_execute(task);
}