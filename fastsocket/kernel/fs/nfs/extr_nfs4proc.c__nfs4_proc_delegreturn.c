#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_task_setup {struct nfs4_delegreturndata* callback_data; int /*<<< orphan*/  flags; int /*<<< orphan*/ * callback_ops; struct rpc_message* rpc_message; int /*<<< orphan*/  rpc_client; } ;
struct rpc_task {int dummy; } ;
struct rpc_message {TYPE_2__* rpc_resp; TYPE_1__* rpc_argp; struct rpc_cred* rpc_cred; int /*<<< orphan*/ * rpc_proc; } ;
struct rpc_cred {int dummy; } ;
struct nfs_server {int /*<<< orphan*/  cache_consistency_bitmask; int /*<<< orphan*/  client; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fattr; struct nfs_server* server; int /*<<< orphan*/  seq_res; } ;
struct TYPE_3__ {int /*<<< orphan*/  bitmask; int /*<<< orphan*/ * stateid; int /*<<< orphan*/ * fhandle; int /*<<< orphan*/  seq_args; } ;
struct nfs4_delegreturndata {int rpc_status; int /*<<< orphan*/  fattr; TYPE_2__ res; TYPE_1__ args; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  stateid; int /*<<< orphan*/  fh; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct rpc_task*) ; 
 size_t NFSPROC4_CLNT_DELEGRETURN ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int PTR_ERR (struct rpc_task*) ; 
 int /*<<< orphan*/  RPC_TASK_ASYNC ; 
 int /*<<< orphan*/  jiffies ; 
 struct nfs4_delegreturndata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs41_init_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfs4_delegreturn_ops ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int nfs4_wait_for_completion_rpc_task (struct rpc_task*) ; 
 int /*<<< orphan*/  nfs_copy_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_post_op_update_inode_force_wcc (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_refresh_inode (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_put_task (struct rpc_task*) ; 
 struct rpc_task* rpc_run_task (struct rpc_task_setup*) ; 

__attribute__((used)) static int _nfs4_proc_delegreturn(struct inode *inode, struct rpc_cred *cred, const nfs4_stateid *stateid, int issync)
{
	struct nfs4_delegreturndata *data;
	struct nfs_server *server = NFS_SERVER(inode);
	struct rpc_task *task;
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_DELEGRETURN],
		.rpc_cred = cred,
	};
	struct rpc_task_setup task_setup_data = {
		.rpc_client = server->client,
		.rpc_message = &msg,
		.callback_ops = &nfs4_delegreturn_ops,
		.flags = RPC_TASK_ASYNC,
	};
	int status = 0;

	data = kzalloc(sizeof(*data), GFP_NOFS);
	if (data == NULL)
		return -ENOMEM;
	nfs41_init_sequence(&data->args.seq_args, &data->res.seq_res, 1);
	data->args.fhandle = &data->fh;
	data->args.stateid = &data->stateid;
	data->args.bitmask = server->cache_consistency_bitmask;
	nfs_copy_fh(&data->fh, NFS_FH(inode));
	nfs4_stateid_copy(&data->stateid, stateid);
	data->res.fattr = &data->fattr;
	data->res.server = server;
	nfs_fattr_init(data->res.fattr);
	data->timestamp = jiffies;
	data->rpc_status = 0;

	task_setup_data.callback_data = data;
	msg.rpc_argp = &data->args,
	msg.rpc_resp = &data->res,
	task = rpc_run_task(&task_setup_data);
	if (IS_ERR(task))
		return PTR_ERR(task);
	if (!issync)
		goto out;
	status = nfs4_wait_for_completion_rpc_task(task);
	if (status != 0)
		goto out;
	status = data->rpc_status;
	if (status == 0)
		nfs_post_op_update_inode_force_wcc(inode, &data->fattr);
	else
		nfs_refresh_inode(inode, &data->fattr);
out:
	rpc_put_task(task);
	return status;
}