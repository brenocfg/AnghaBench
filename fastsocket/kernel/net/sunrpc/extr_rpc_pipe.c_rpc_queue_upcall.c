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
struct rpc_pipe_msg {scalar_t__ len; int /*<<< orphan*/  list; } ;
struct rpc_inode {int flags; int /*<<< orphan*/  waitq; int /*<<< orphan*/  pipelen; int /*<<< orphan*/  pipe; int /*<<< orphan*/  queue_timeout; scalar_t__ nreaders; int /*<<< orphan*/ * ops; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int EPIPE ; 
 struct rpc_inode* RPC_I (struct inode*) ; 
 int RPC_PIPE_WAIT_FOR_OPEN ; 
 int /*<<< orphan*/  RPC_UPCALL_TIMEOUT ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpciod_workqueue ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int
rpc_queue_upcall(struct inode *inode, struct rpc_pipe_msg *msg)
{
	struct rpc_inode *rpci = RPC_I(inode);
	int res = -EPIPE;

	spin_lock(&inode->i_lock);
	if (rpci->ops == NULL)
		goto out;
	if (rpci->nreaders) {
		list_add_tail(&msg->list, &rpci->pipe);
		rpci->pipelen += msg->len;
		res = 0;
	} else if (rpci->flags & RPC_PIPE_WAIT_FOR_OPEN) {
		if (list_empty(&rpci->pipe))
			queue_delayed_work(rpciod_workqueue,
					&rpci->queue_timeout,
					RPC_UPCALL_TIMEOUT);
		list_add_tail(&msg->list, &rpci->pipe);
		rpci->pipelen += msg->len;
		res = 0;
	}
out:
	spin_unlock(&inode->i_lock);
	wake_up(&rpci->waitq);
	return res;
}