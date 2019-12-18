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
struct rpc_task {int dummy; } ;
struct nfs_seqid {int dummy; } ;
struct nfs_inode {int /*<<< orphan*/  rwsem; } ;
struct nfs4_state_owner {int /*<<< orphan*/  so_delegreturn_mutex; } ;
struct nfs4_state {int /*<<< orphan*/  flags; struct nfs4_state_owner* owner; struct inode* inode; } ;
struct nfs4_lock_state {int /*<<< orphan*/  ls_seqid; } ;
struct inode {int dummy; } ;
struct TYPE_3__ {struct nfs4_lock_state* owner; } ;
struct TYPE_4__ {TYPE_1__ nfs4_fl; } ;
struct file_lock {unsigned char fl_flags; int /*<<< orphan*/  fl_file; TYPE_2__ fl_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int ENOMEM ; 
 unsigned char FL_EXISTS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct rpc_task*) ; 
 int /*<<< orphan*/  NFS_DELEGATED_STATE ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int PTR_ERR (struct rpc_task*) ; 
 int /*<<< orphan*/  do_vfs_lock (int /*<<< orphan*/ ,struct file_lock*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rpc_task* nfs4_do_unlck (struct file_lock*,int /*<<< orphan*/ ,struct nfs4_lock_state*,struct nfs_seqid*) ; 
 int nfs4_set_lock_state (struct nfs4_state*,struct file_lock*) ; 
 int nfs4_wait_for_completion_rpc_task (struct rpc_task*) ; 
 struct nfs_seqid* nfs_alloc_seqid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_file_open_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_put_task (struct rpc_task*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_proc_unlck(struct nfs4_state *state, int cmd, struct file_lock *request)
{
	struct inode *inode = state->inode;
	struct nfs4_state_owner *sp = state->owner;
	struct nfs_inode *nfsi = NFS_I(inode);
	struct nfs_seqid *seqid;
	struct nfs4_lock_state *lsp;
	struct rpc_task *task;
	int status = 0;
	unsigned char fl_flags = request->fl_flags;

	status = nfs4_set_lock_state(state, request);
	/* Unlock _before_ we do the RPC call */
	request->fl_flags |= FL_EXISTS;
	/* Exclude nfs_delegation_claim_locks() */
	mutex_lock(&sp->so_delegreturn_mutex);
	/* Exclude nfs4_reclaim_open_stateid() - note nesting! */
	down_read(&nfsi->rwsem);
	if (do_vfs_lock(request->fl_file, request) == -ENOENT) {
		up_read(&nfsi->rwsem);
		mutex_unlock(&sp->so_delegreturn_mutex);
		goto out;
	}
	up_read(&nfsi->rwsem);
	mutex_unlock(&sp->so_delegreturn_mutex);
	if (status != 0)
		goto out;
	/* Is this a delegated lock? */
	if (test_bit(NFS_DELEGATED_STATE, &state->flags))
		goto out;
	lsp = request->fl_u.nfs4_fl.owner;
	seqid = nfs_alloc_seqid(&lsp->ls_seqid, GFP_KERNEL);
	status = -ENOMEM;
	if (seqid == NULL)
		goto out;
	task = nfs4_do_unlck(request, nfs_file_open_context(request->fl_file), lsp, seqid);
	status = PTR_ERR(task);
	if (IS_ERR(task))
		goto out;
	status = nfs4_wait_for_completion_rpc_task(task);
	rpc_put_task(task);
out:
	request->fl_flags = fl_flags;
	return status;
}