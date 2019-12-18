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
struct rpc_pipe_ops {int /*<<< orphan*/  (* release_pipe ) (struct inode*) ;int /*<<< orphan*/  destroy_msg; } ;
struct rpc_inode {scalar_t__ nreaders; scalar_t__ nwriters; int /*<<< orphan*/  queue_timeout; struct rpc_pipe_ops* ops; scalar_t__ pipelen; int /*<<< orphan*/  pipe; int /*<<< orphan*/  in_upcall; } ;
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 struct rpc_inode* RPC_I (struct inode*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_list ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_inode_setowner (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_purge_list (struct rpc_inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct inode*) ; 

__attribute__((used)) static void
rpc_close_pipes(struct inode *inode)
{
	struct rpc_inode *rpci = RPC_I(inode);
	const struct rpc_pipe_ops *ops;
	int need_release;

	mutex_lock(&inode->i_mutex);
	ops = rpci->ops;
	if (ops != NULL) {
		LIST_HEAD(free_list);
		spin_lock(&inode->i_lock);
		need_release = rpci->nreaders != 0 || rpci->nwriters != 0;
		rpci->nreaders = 0;
		list_splice_init(&rpci->in_upcall, &free_list);
		list_splice_init(&rpci->pipe, &free_list);
		rpci->pipelen = 0;
		rpci->ops = NULL;
		spin_unlock(&inode->i_lock);
		rpc_purge_list(rpci, &free_list, ops->destroy_msg, -EPIPE);
		rpci->nwriters = 0;
		if (need_release && ops->release_pipe)
			ops->release_pipe(inode);
		cancel_delayed_work_sync(&rpci->queue_timeout);
	}
	rpc_inode_setowner(inode, NULL);
	mutex_unlock(&inode->i_mutex);
}