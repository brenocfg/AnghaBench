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
struct rpc_inode {int /*<<< orphan*/  pipe; int /*<<< orphan*/ * ops; int /*<<< orphan*/  waitq; } ;
struct poll_table_struct {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {scalar_t__ private_data; TYPE_2__ f_path; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 unsigned int POLLERR ; 
 unsigned int POLLHUP ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 struct rpc_inode* RPC_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,struct poll_table_struct*) ; 

__attribute__((used)) static unsigned int
rpc_pipe_poll(struct file *filp, struct poll_table_struct *wait)
{
	struct rpc_inode *rpci;
	unsigned int mask = 0;

	rpci = RPC_I(filp->f_path.dentry->d_inode);
	poll_wait(filp, &rpci->waitq, wait);

	mask = POLLOUT | POLLWRNORM;
	if (rpci->ops == NULL)
		mask |= POLLERR | POLLHUP;
	if (filp->private_data || !list_empty(&rpci->pipe))
		mask |= POLLIN | POLLRDNORM;
	return mask;
}