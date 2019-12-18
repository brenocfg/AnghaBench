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
struct rpc_task {struct rpc_clnt* tk_client; int /*<<< orphan*/  tk_task; } ;
struct rpc_clnt {int /*<<< orphan*/  cl_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_release_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void rpc_task_release_client(struct rpc_task *task)
{
	struct rpc_clnt *clnt = task->tk_client;

	if (clnt != NULL) {
		/* Remove from client task list */
		spin_lock(&clnt->cl_lock);
		list_del(&task->tk_task);
		spin_unlock(&clnt->cl_lock);
		task->tk_client = NULL;

		rpc_release_client(clnt);
	}
}