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
struct pipe_inode_info {int /*<<< orphan*/  fasync_readers; int /*<<< orphan*/  fasync_writers; } ;
struct inode {int /*<<< orphan*/  i_mutex; struct pipe_inode_info* i_pipe; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pipe_rdwr_fasync(int fd, struct file *filp, int on)
{
	struct inode *inode = filp->f_path.dentry->d_inode;
	struct pipe_inode_info *pipe = inode->i_pipe;
	int retval;

	mutex_lock(&inode->i_mutex);
	retval = fasync_helper(fd, filp, on, &pipe->fasync_readers);
	if (retval >= 0) {
		retval = fasync_helper(fd, filp, on, &pipe->fasync_writers);
		if (retval < 0) /* this can happen only if on == T */
			fasync_helper(-1, filp, 0, &pipe->fasync_readers);
	}
	mutex_unlock(&inode->i_mutex);
	return retval;
}