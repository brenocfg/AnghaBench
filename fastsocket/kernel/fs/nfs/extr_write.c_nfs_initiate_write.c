#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rpc_task_setup {int priority; int /*<<< orphan*/  flags; int /*<<< orphan*/  workqueue; struct nfs_write_data* callback_data; struct rpc_call_ops const* callback_ops; struct rpc_message* rpc_message; TYPE_2__* task; struct rpc_clnt* rpc_client; } ;
struct rpc_task {int tk_status; } ;
struct rpc_message {int /*<<< orphan*/  rpc_cred; int /*<<< orphan*/ * rpc_resp; TYPE_4__* rpc_argp; } ;
struct rpc_clnt {int dummy; } ;
struct rpc_call_ops {int dummy; } ;
struct TYPE_9__ {scalar_t__ offset; int /*<<< orphan*/  count; } ;
struct TYPE_7__ {int /*<<< orphan*/  tk_pid; } ;
struct nfs_write_data {TYPE_4__ args; TYPE_2__ task; TYPE_1__* header; int /*<<< orphan*/  res; } ;
struct inode {TYPE_3__* i_sb; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* write_setup ) (struct nfs_write_data*,struct rpc_message*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  s_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  cred; struct inode* inode; } ;

/* Variables and functions */
 int FLUSH_SYNC ; 
 scalar_t__ IS_ERR (struct rpc_task*) ; 
 scalar_t__ NFS_FILEID (struct inode*) ; 
 TYPE_5__* NFS_PROTO (struct inode*) ; 
 int PTR_ERR (struct rpc_task*) ; 
 int /*<<< orphan*/  RPC_TASK_ASYNC ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long,int /*<<< orphan*/ ,unsigned long long) ; 
 int flush_task_priority (int) ; 
 int /*<<< orphan*/  nfsiod_workqueue ; 
 int /*<<< orphan*/  rpc_put_task (struct rpc_task*) ; 
 struct rpc_task* rpc_run_task (struct rpc_task_setup*) ; 
 int rpc_wait_for_completion_task (struct rpc_task*) ; 
 int /*<<< orphan*/  stub1 (struct nfs_write_data*,struct rpc_message*) ; 

int nfs_initiate_write(struct rpc_clnt *clnt,
		       struct nfs_write_data *data,
		       const struct rpc_call_ops *call_ops,
		       int how)
{
	struct inode *inode = data->header->inode;
	int priority = flush_task_priority(how);
	struct rpc_task *task;
	struct rpc_message msg = {
		.rpc_argp = &data->args,
		.rpc_resp = &data->res,
		.rpc_cred = data->header->cred,
	};
	struct rpc_task_setup task_setup_data = {
		.rpc_client = clnt,
		.task = &data->task,
		.rpc_message = &msg,
		.callback_ops = call_ops,
		.callback_data = data,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC,
		.priority = priority,
	};
	int ret = 0;

	/* Set up the initial task struct.  */
	NFS_PROTO(inode)->write_setup(data, &msg);

	dprintk("NFS: %5u initiated write call "
		"(req %s/%lld, %u bytes @ offset %llu)\n",
		data->task.tk_pid,
		inode->i_sb->s_id,
		(long long)NFS_FILEID(inode),
		data->args.count,
		(unsigned long long)data->args.offset);

	task = rpc_run_task(&task_setup_data);
	if (IS_ERR(task)) {
		ret = PTR_ERR(task);
		goto out;
	}
	if (how & FLUSH_SYNC) {
		ret = rpc_wait_for_completion_task(task);
		if (ret == 0)
			ret = task->tk_status;
	}
	rpc_put_task(task);
out:
	return ret;
}