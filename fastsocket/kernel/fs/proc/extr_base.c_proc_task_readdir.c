#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct task_struct {struct task_struct* group_leader; } ;
struct pid_namespace {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct TYPE_4__ {struct dentry* dentry; } ;
struct file {scalar_t__ f_version; scalar_t__ f_pos; TYPE_3__* f_dentry; TYPE_1__ f_path; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  ino_t ;
typedef  int /*<<< orphan*/  (* filldir_t ) (void*,char*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_6__ {TYPE_2__* d_sb; } ;
struct TYPE_5__ {struct pid_namespace* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_DIR ; 
 int ENOENT ; 
 struct task_struct* first_tid (struct task_struct*,int,scalar_t__,struct pid_namespace*) ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 struct task_struct* next_tid (struct task_struct*) ; 
 int /*<<< orphan*/  parent_ino (struct dentry*) ; 
 scalar_t__ pid_alive (struct task_struct*) ; 
 scalar_t__ proc_task_fill_cache (struct file*,void*,int /*<<< orphan*/  (*) (void*,char*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ),struct task_struct*,int) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int task_pid_nr_ns (struct task_struct*,struct pid_namespace*) ; 

__attribute__((used)) static int proc_task_readdir(struct file * filp, void * dirent, filldir_t filldir)
{
	struct dentry *dentry = filp->f_path.dentry;
	struct inode *inode = dentry->d_inode;
	struct task_struct *leader = NULL;
	struct task_struct *task;
	int retval = -ENOENT;
	ino_t ino;
	int tid;
	struct pid_namespace *ns;

	task = get_proc_task(inode);
	if (!task)
		goto out_no_task;
	rcu_read_lock();
	if (pid_alive(task)) {
		leader = task->group_leader;
		get_task_struct(leader);
	}
	rcu_read_unlock();
	put_task_struct(task);
	if (!leader)
		goto out_no_task;
	retval = 0;

	switch ((unsigned long)filp->f_pos) {
	case 0:
		ino = inode->i_ino;
		if (filldir(dirent, ".", 1, filp->f_pos, ino, DT_DIR) < 0)
			goto out;
		filp->f_pos++;
		/* fall through */
	case 1:
		ino = parent_ino(dentry);
		if (filldir(dirent, "..", 2, filp->f_pos, ino, DT_DIR) < 0)
			goto out;
		filp->f_pos++;
		/* fall through */
	}

	/* f_version caches the tgid value that the last readdir call couldn't
	 * return. lseek aka telldir automagically resets f_version to 0.
	 */
	ns = filp->f_dentry->d_sb->s_fs_info;
	tid = (int)filp->f_version;
	filp->f_version = 0;
	for (task = first_tid(leader, tid, filp->f_pos - 2, ns);
	     task;
	     task = next_tid(task), filp->f_pos++) {
		tid = task_pid_nr_ns(task, ns);
		if (proc_task_fill_cache(filp, dirent, filldir, task, tid) < 0) {
			/* returning this tgid failed, save it as the first
			 * pid for the next readir call */
			filp->f_version = (u64)tid;
			put_task_struct(task);
			break;
		}
	}
out:
	put_task_struct(leader);
out_no_task:
	return retval;
}