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
struct nameidata {int dummy; } ;
struct inode {int i_mode; scalar_t__ i_gid; scalar_t__ i_uid; } ;
struct files_struct {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
struct cred {scalar_t__ egid; scalar_t__ euid; } ;

/* Variables and functions */
 int S_ISGID ; 
 int S_ISUID ; 
 struct cred* __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 scalar_t__ fcheck_files (struct files_struct*,int) ; 
 struct files_struct* get_files_struct (struct task_struct*) ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 int proc_fd (struct inode*) ; 
 int /*<<< orphan*/  put_files_struct (struct files_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  security_task_to_inode (struct task_struct*,struct inode*) ; 
 scalar_t__ task_dumpable (struct task_struct*) ; 

__attribute__((used)) static int tid_fd_revalidate(struct dentry *dentry, struct nameidata *nd)
{
	struct inode *inode = dentry->d_inode;
	struct task_struct *task = get_proc_task(inode);
	int fd = proc_fd(inode);
	struct files_struct *files;
	const struct cred *cred;

	if (task) {
		files = get_files_struct(task);
		if (files) {
			rcu_read_lock();
			if (fcheck_files(files, fd)) {
				rcu_read_unlock();
				put_files_struct(files);
				if (task_dumpable(task)) {
					rcu_read_lock();
					cred = __task_cred(task);
					inode->i_uid = cred->euid;
					inode->i_gid = cred->egid;
					rcu_read_unlock();
				} else {
					inode->i_uid = 0;
					inode->i_gid = 0;
				}
				inode->i_mode &= ~(S_ISUID | S_ISGID);
				security_task_to_inode(task, inode);
				put_task_struct(task);
				return 1;
			}
			rcu_read_unlock();
			put_files_struct(files);
		}
		put_task_struct(task);
	}
	d_drop(dentry);
	return 0;
}