#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpc_pipe_msg {int /*<<< orphan*/  list; int /*<<< orphan*/  errno; } ;
struct rpc_inode {scalar_t__ nwriters; scalar_t__ nreaders; TYPE_1__* ops; scalar_t__ pipelen; int /*<<< orphan*/  pipe; } ;
struct inode {int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_lock; } ;
struct file {int f_mode; scalar_t__ private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release_pipe ) (struct inode*) ;int /*<<< orphan*/  (* destroy_msg ) (struct rpc_pipe_msg*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 struct rpc_inode* RPC_I (struct inode*) ; 
 int /*<<< orphan*/  free_list ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_purge_list (struct rpc_inode*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct rpc_pipe_msg*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rpc_pipe_msg*) ; 
 int /*<<< orphan*/  stub2 (struct inode*) ; 

__attribute__((used)) static int
rpc_pipe_release(struct inode *inode, struct file *filp)
{
	struct rpc_inode *rpci = RPC_I(inode);
	struct rpc_pipe_msg *msg;
	int last_close;

	mutex_lock(&inode->i_mutex);
	if (rpci->ops == NULL)
		goto out;
	msg = (struct rpc_pipe_msg *)filp->private_data;
	if (msg != NULL) {
		spin_lock(&inode->i_lock);
		msg->errno = -EAGAIN;
		list_del_init(&msg->list);
		spin_unlock(&inode->i_lock);
		rpci->ops->destroy_msg(msg);
	}
	if (filp->f_mode & FMODE_WRITE)
		rpci->nwriters --;
	if (filp->f_mode & FMODE_READ) {
		rpci->nreaders --;
		if (rpci->nreaders == 0) {
			LIST_HEAD(free_list);
			spin_lock(&inode->i_lock);
			list_splice_init(&rpci->pipe, &free_list);
			rpci->pipelen = 0;
			spin_unlock(&inode->i_lock);
			rpc_purge_list(rpci, &free_list,
					rpci->ops->destroy_msg, -EAGAIN);
		}
	}
	last_close = rpci->nwriters == 0 && rpci->nreaders == 0;
	if (last_close && rpci->ops->release_pipe)
		rpci->ops->release_pipe(inode);
out:
	mutex_unlock(&inode->i_mutex);
	return 0;
}