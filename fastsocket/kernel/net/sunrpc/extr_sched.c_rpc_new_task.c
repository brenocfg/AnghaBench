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
struct rpc_task_setup {int /*<<< orphan*/  callback_data; int /*<<< orphan*/  callback_ops; struct rpc_task* task; } ;
struct rpc_task {unsigned short tk_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct rpc_task* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned short RPC_TASK_DYNAMIC ; 
 int /*<<< orphan*/  dprintk (char*,struct rpc_task*) ; 
 struct rpc_task* rpc_alloc_task () ; 
 int /*<<< orphan*/  rpc_init_task (struct rpc_task*,struct rpc_task_setup const*) ; 
 int /*<<< orphan*/  rpc_release_calldata (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct rpc_task *rpc_new_task(const struct rpc_task_setup *setup_data)
{
	struct rpc_task	*task = setup_data->task;
	unsigned short flags = 0;

	if (task == NULL) {
		task = rpc_alloc_task();
		if (task == NULL) {
			rpc_release_calldata(setup_data->callback_ops,
					setup_data->callback_data);
			return ERR_PTR(-ENOMEM);
		}
		flags = RPC_TASK_DYNAMIC;
	}

	rpc_init_task(task, setup_data);
	task->tk_flags |= flags;
	dprintk("RPC:       allocated task %p\n", task);
	return task;
}