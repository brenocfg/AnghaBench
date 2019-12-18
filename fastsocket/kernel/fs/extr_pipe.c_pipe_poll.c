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
struct pipe_inode_info {int nrbufs; scalar_t__ w_counter; int /*<<< orphan*/  readers; int /*<<< orphan*/  writers; int /*<<< orphan*/  wait; } ;
struct inode {struct pipe_inode_info* i_pipe; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {int f_mode; scalar_t__ f_version; TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  poll_table ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int PIPE_BUFFERS ; 
 unsigned int POLLERR ; 
 unsigned int POLLHUP ; 
 unsigned int POLLIN ; 
 unsigned int POLLOUT ; 
 unsigned int POLLRDNORM ; 
 unsigned int POLLWRNORM ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
pipe_poll(struct file *filp, poll_table *wait)
{
	unsigned int mask;
	struct inode *inode = filp->f_path.dentry->d_inode;
	struct pipe_inode_info *pipe = inode->i_pipe;
	int nrbufs;

	poll_wait(filp, &pipe->wait, wait);

	/* Reading only -- no need for acquiring the semaphore.  */
	nrbufs = pipe->nrbufs;
	mask = 0;
	if (filp->f_mode & FMODE_READ) {
		mask = (nrbufs > 0) ? POLLIN | POLLRDNORM : 0;
		if (!pipe->writers && filp->f_version != pipe->w_counter)
			mask |= POLLHUP;
	}

	if (filp->f_mode & FMODE_WRITE) {
		mask |= (nrbufs < PIPE_BUFFERS) ? POLLOUT | POLLWRNORM : 0;
		/*
		 * Most Unices do not set POLLERR for FIFOs but on Linux they
		 * behave exactly like pipes for poll().
		 */
		if (!pipe->readers)
			mask |= POLLERR;
	}

	return mask;
}