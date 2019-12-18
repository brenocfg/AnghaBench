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
struct rpc_task {int /*<<< orphan*/ * tk_action; } ;
struct TYPE_5__ {int /*<<< orphan*/  seq_res; } ;
struct TYPE_6__ {int /*<<< orphan*/  seqid; int /*<<< orphan*/  seq_args; } ;
struct nfs4_unlockdata {TYPE_2__ res; TYPE_3__ arg; int /*<<< orphan*/  server; int /*<<< orphan*/  timestamp; TYPE_1__* lsp; } ;
struct TYPE_4__ {int ls_flags; } ;

/* Variables and functions */
 int NFS_LOCK_INITIALIZED ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  nfs4_sequence_done (struct rpc_task*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfs4_setup_sequence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_task*) ; 
 int /*<<< orphan*/  nfs_release_seqid (int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_wait_on_sequence (int /*<<< orphan*/ ,struct rpc_task*) ; 
 int /*<<< orphan*/  rpc_call_start (struct rpc_task*) ; 

__attribute__((used)) static void nfs4_locku_prepare(struct rpc_task *task, void *data)
{
	struct nfs4_unlockdata *calldata = data;

	if (nfs_wait_on_sequence(calldata->arg.seqid, task) != 0)
		goto out_wait;
	if ((calldata->lsp->ls_flags & NFS_LOCK_INITIALIZED) == 0) {
		/* Note: exit _without_ running nfs4_locku_done */
		goto out_no_action;
	}
	calldata->timestamp = jiffies;
	if (nfs4_setup_sequence(calldata->server,
				&calldata->arg.seq_args,
				&calldata->res.seq_res,
				task) != 0)
		nfs_release_seqid(calldata->arg.seqid);
	else
		rpc_call_start(task);
	return;
out_no_action:
	task->tk_action = NULL;
out_wait:
	nfs4_sequence_done(task, &calldata->res.seq_res);
}