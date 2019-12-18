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
struct task_struct {int dummy; } ;
struct super_block {int dummy; } ;
struct proc_inode {int /*<<< orphan*/  pid; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; } ;
struct cred {int /*<<< orphan*/  egid; int /*<<< orphan*/  euid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 struct proc_inode* PROC_I (struct inode*) ; 
 struct cred* __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  get_task_pid (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  proc_def_inode_operations ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  security_task_to_inode (struct task_struct*,struct inode*) ; 
 scalar_t__ task_dumpable (struct task_struct*) ; 

struct inode *proc_pid_make_inode(struct super_block * sb, struct task_struct *task)
{
	struct inode * inode;
	struct proc_inode *ei;
	const struct cred *cred;

	/* We need a new inode */

	inode = new_inode(sb);
	if (!inode)
		goto out;

	/* Common stuff */
	ei = PROC_I(inode);
	inode->i_mtime = inode->i_atime = inode->i_ctime = CURRENT_TIME;
	inode->i_op = &proc_def_inode_operations;

	/*
	 * grab the reference to task.
	 */
	ei->pid = get_task_pid(task, PIDTYPE_PID);
	if (!ei->pid)
		goto out_unlock;

	if (task_dumpable(task)) {
		rcu_read_lock();
		cred = __task_cred(task);
		inode->i_uid = cred->euid;
		inode->i_gid = cred->egid;
		rcu_read_unlock();
	}
	security_task_to_inode(task, inode);

out:
	return inode;

out_unlock:
	iput(inode);
	return NULL;
}