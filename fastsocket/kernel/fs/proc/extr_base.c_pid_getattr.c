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
struct vfsmount {int dummy; } ;
struct task_struct {int dummy; } ;
struct pid_namespace {int dummy; } ;
struct kstat {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct inode {int i_mode; } ;
struct dentry {TYPE_1__* d_sb; struct inode* d_inode; } ;
struct cred {int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; } ;
struct TYPE_2__ {struct pid_namespace* s_fs_info; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IXUGO ; 
 struct cred* __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 int /*<<< orphan*/  has_pid_permissions (struct pid_namespace*,struct task_struct*,int) ; 
 struct task_struct* pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_pid (struct inode*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ task_dumpable (struct task_struct*) ; 

int pid_getattr(struct vfsmount *mnt, struct dentry *dentry, struct kstat *stat)
{
	struct inode *inode = dentry->d_inode;
	struct task_struct *task;
	const struct cred *cred;
	struct pid_namespace *pid = dentry->d_sb->s_fs_info;

	generic_fillattr(inode, stat);

	rcu_read_lock();
	stat->uid = 0;
	stat->gid = 0;
	task = pid_task(proc_pid(inode), PIDTYPE_PID);
	if (task) {
		if (!has_pid_permissions(pid, task, 2)) {
			rcu_read_unlock();
			/*
			 * This doesn't prevent learning whether PID exists,
			 * it only makes getattr() consistent with readdir().
			 */
			return -ENOENT;
		}
		if ((inode->i_mode == (S_IFDIR|S_IRUGO|S_IXUGO)) ||
		    task_dumpable(task)) {
			cred = __task_cred(task);
			stat->uid = cred->euid;
			stat->gid = cred->egid;
		}
	}
	rcu_read_unlock();
	return 0;
}