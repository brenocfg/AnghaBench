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
struct TYPE_2__ {int /*<<< orphan*/  proc_get_link; } ;
struct proc_inode {unsigned int fd; TYPE_1__ op; } ;
struct inode {int i_mode; int i_size; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_sb; } ;
struct files_struct {int /*<<< orphan*/  file_lock; } ;
struct file {int f_mode; } ;
struct dentry {int /*<<< orphan*/ * d_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 struct proc_inode* PROC_I (struct inode*) ; 
 int S_IFLNK ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct file* fcheck_files (struct files_struct*,unsigned int) ; 
 struct files_struct* get_files_struct (struct task_struct*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  proc_fd_link ; 
 int /*<<< orphan*/  proc_pid_link_inode_operations ; 
 struct inode* proc_pid_make_inode (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  put_files_struct (struct files_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tid_fd_dentry_operations ; 
 scalar_t__ tid_fd_revalidate (struct dentry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *proc_fd_instantiate(struct inode *dir,
	struct dentry *dentry, struct task_struct *task, const void *ptr)
{
	unsigned fd = *(const unsigned *)ptr;
	struct file *file;
	struct files_struct *files;
 	struct inode *inode;
 	struct proc_inode *ei;
	struct dentry *error = ERR_PTR(-ENOENT);

	inode = proc_pid_make_inode(dir->i_sb, task);
	if (!inode)
		goto out;
	ei = PROC_I(inode);
	ei->fd = fd;
	files = get_files_struct(task);
	if (!files)
		goto out_iput;
	inode->i_mode = S_IFLNK;

	/*
	 * We are not taking a ref to the file structure, so we must
	 * hold ->file_lock.
	 */
	spin_lock(&files->file_lock);
	file = fcheck_files(files, fd);
	if (!file)
		goto out_unlock;
	if (file->f_mode & FMODE_READ)
		inode->i_mode |= S_IRUSR | S_IXUSR;
	if (file->f_mode & FMODE_WRITE)
		inode->i_mode |= S_IWUSR | S_IXUSR;
	spin_unlock(&files->file_lock);
	put_files_struct(files);

	inode->i_op = &proc_pid_link_inode_operations;
	inode->i_size = 64;
	ei->op.proc_get_link = proc_fd_link;
	dentry->d_op = &tid_fd_dentry_operations;
	d_add(dentry, inode);
	/* Close the race of the process dying before we return the dentry */
	if (tid_fd_revalidate(dentry, NULL))
		error = NULL;

 out:
	return error;
out_unlock:
	spin_unlock(&files->file_lock);
	put_files_struct(files);
out_iput:
	iput(inode);
	goto out;
}