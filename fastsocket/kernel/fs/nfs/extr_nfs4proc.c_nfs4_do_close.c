#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rpc_task_setup {struct nfs4_closedata* callback_data; int /*<<< orphan*/  flags; int /*<<< orphan*/  workqueue; int /*<<< orphan*/ * callback_ops; struct rpc_message* rpc_message; int /*<<< orphan*/  rpc_client; } ;
struct rpc_task {int dummy; } ;
struct rpc_message {TYPE_2__* rpc_resp; TYPE_1__* rpc_argp; int /*<<< orphan*/  rpc_cred; int /*<<< orphan*/ * rpc_proc; } ;
struct nfs_server {int /*<<< orphan*/  cache_consistency_bitmask; int /*<<< orphan*/  client; } ;
struct nfs4_state_owner {int /*<<< orphan*/  so_seqid; int /*<<< orphan*/  so_cred; } ;
struct nfs4_state {TYPE_3__* inode; struct nfs4_state_owner* owner; int /*<<< orphan*/  open_stateid; } ;
struct TYPE_7__ {struct nfs_server* server; int /*<<< orphan*/ * seqid; int /*<<< orphan*/ * fattr; int /*<<< orphan*/  seq_res; } ;
struct TYPE_6__ {int /*<<< orphan*/ * seqid; int /*<<< orphan*/  bitmask; scalar_t__ fmode; int /*<<< orphan*/ * stateid; int /*<<< orphan*/  fh; int /*<<< orphan*/  seq_args; } ;
struct nfs4_closedata {int roc; TYPE_2__ res; TYPE_1__ arg; TYPE_3__* inode; int /*<<< orphan*/  fattr; struct nfs4_state* state; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct rpc_task*) ; 
 size_t NFSPROC4_CLNT_CLOSE ; 
 int /*<<< orphan*/  NFS_FH (TYPE_3__*) ; 
 struct nfs_server* NFS_SERVER (TYPE_3__*) ; 
 int PTR_ERR (struct rpc_task*) ; 
 int /*<<< orphan*/  RPC_TASK_ASYNC ; 
 int /*<<< orphan*/  kfree (struct nfs4_closedata*) ; 
 struct nfs4_closedata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs41_init_sequence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfs4_close_ops ; 
 int /*<<< orphan*/ * nfs4_procedures ; 
 int /*<<< orphan*/  nfs4_put_open_state (struct nfs4_state*) ; 
 int /*<<< orphan*/  nfs4_put_state_owner (struct nfs4_state_owner*) ; 
 int /*<<< orphan*/ * nfs_alloc_seqid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_sb_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsiod_workqueue ; 
 int /*<<< orphan*/  pnfs_roc_release (TYPE_3__*) ; 
 int /*<<< orphan*/  rpc_put_task (struct rpc_task*) ; 
 struct rpc_task* rpc_run_task (struct rpc_task_setup*) ; 
 int rpc_wait_for_completion_task (struct rpc_task*) ; 

int nfs4_do_close(struct nfs4_state *state, gfp_t gfp_mask, int wait, bool roc)
{
	struct nfs_server *server = NFS_SERVER(state->inode);
	struct nfs4_closedata *calldata;
	struct nfs4_state_owner *sp = state->owner;
	struct rpc_task *task;
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_CLOSE],
		.rpc_cred = state->owner->so_cred,
	};
	struct rpc_task_setup task_setup_data = {
		.rpc_client = server->client,
		.rpc_message = &msg,
		.callback_ops = &nfs4_close_ops,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC,
	};
	int status = -ENOMEM;

	calldata = kzalloc(sizeof(*calldata), gfp_mask);
	if (calldata == NULL)
		goto out;
	nfs41_init_sequence(&calldata->arg.seq_args, &calldata->res.seq_res, 1);
	calldata->inode = state->inode;
	calldata->state = state;
	calldata->arg.fh = NFS_FH(state->inode);
	calldata->arg.stateid = &state->open_stateid;
	/* Serialization for the sequence id */
	calldata->arg.seqid = nfs_alloc_seqid(&state->owner->so_seqid, gfp_mask);
	if (calldata->arg.seqid == NULL)
		goto out_free_calldata;
	calldata->arg.fmode = 0;
	calldata->arg.bitmask = server->cache_consistency_bitmask;
	calldata->res.fattr = &calldata->fattr;
	calldata->res.seqid = calldata->arg.seqid;
	calldata->res.server = server;
	calldata->roc = roc;
	nfs_sb_active(calldata->inode->i_sb);

	msg.rpc_argp = &calldata->arg,
	msg.rpc_resp = &calldata->res,
	task_setup_data.callback_data = calldata;
	task = rpc_run_task(&task_setup_data);
	if (IS_ERR(task))
		return PTR_ERR(task);
	status = 0;
	if (wait)
		status = rpc_wait_for_completion_task(task);
	rpc_put_task(task);
	return status;
out_free_calldata:
	kfree(calldata);
out:
	if (roc)
		pnfs_roc_release(state->inode);
	nfs4_put_open_state(state);
	nfs4_put_state_owner(sp);
	return status;
}