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
struct perf_event {int /*<<< orphan*/  fasync; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {struct perf_event* private_data; TYPE_2__ f_path; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int perf_fasync(int fd, struct file *filp, int on)
{
	struct inode *inode = filp->f_path.dentry->d_inode;
	struct perf_event *event = filp->private_data;
	int retval;

	mutex_lock(&inode->i_mutex);
	retval = fasync_helper(fd, filp, on, &event->fasync);
	mutex_unlock(&inode->i_mutex);

	if (retval < 0)
		return retval;

	return 0;
}