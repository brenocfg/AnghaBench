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
struct task_struct {int dummy; } ;
struct proc_ns_operations {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {int f_pos; TYPE_1__ f_path; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  ino_t ;
typedef  int /*<<< orphan*/  (* filldir_t ) (void*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int ARRAY_SIZE (struct proc_ns_operations**) ; 
 int /*<<< orphan*/  DT_DIR ; 
 int ENOENT ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 struct proc_ns_operations** ns_entries ; 
 int /*<<< orphan*/  parent_ino (struct dentry*) ; 
 int /*<<< orphan*/  proc_ns_fill_cache (struct file*,void*,int /*<<< orphan*/  (*) (void*,char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ),struct task_struct*,struct proc_ns_operations const*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

__attribute__((used)) static int proc_ns_dir_readdir(struct file *filp, void *dirent,
				filldir_t filldir)
{
	int i;
	struct dentry *dentry = filp->f_path.dentry;
	struct inode *inode = dentry->d_inode;
	struct task_struct *task = get_proc_task(inode);
	const struct proc_ns_operations **entry, **last;
	ino_t ino;
	int ret;

	ret = -ENOENT;
	if (!task)
		goto out_no_task;

	ret = 0;
	i = filp->f_pos;
	switch (i) {
	case 0:
		ino = inode->i_ino;
		if (filldir(dirent, ".", 1, i, ino, DT_DIR) < 0)
			goto out;
		i++;
		filp->f_pos++;
		/* fall through */
	case 1:
		ino = parent_ino(dentry);
		if (filldir(dirent, "..", 2, i, ino, DT_DIR) < 0)
			goto out;
		i++;
		filp->f_pos++;
		/* fall through */
	default:
		i -= 2;
		if (i >= ARRAY_SIZE(ns_entries)) {
			ret = 1;
			goto out;
		}
		entry = ns_entries + i;
		last = &ns_entries[ARRAY_SIZE(ns_entries) - 1];
		while (entry <= last) {
			if (proc_ns_fill_cache(filp, dirent, filldir,
						task, *entry) < 0)
				goto out;
			filp->f_pos++;
			entry++;
		}
	}

	ret = 1;
out:
	put_task_struct(task);
out_no_task:
	return ret;
}