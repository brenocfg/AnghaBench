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
struct inode {int i_mode; scalar_t__ i_nlink; int /*<<< orphan*/  i_flags; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/ * d_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  S_IMMUTABLE ; 
 int S_IRUGO ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  pid_dentry_operations ; 
 scalar_t__ pid_entry_count_dirs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pid_revalidate (struct dentry*,int /*<<< orphan*/ *) ; 
 struct inode* proc_pid_make_inode (int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  proc_tgid_base_inode_operations ; 
 int /*<<< orphan*/  proc_tgid_base_operations ; 
 int /*<<< orphan*/  tgid_base_stuff ; 

__attribute__((used)) static struct dentry *proc_pid_instantiate(struct inode *dir,
					   struct dentry * dentry,
					   struct task_struct *task, const void *ptr)
{
	struct dentry *error = ERR_PTR(-ENOENT);
	struct inode *inode;

	inode = proc_pid_make_inode(dir->i_sb, task);
	if (!inode)
		goto out;

	inode->i_mode = S_IFDIR|S_IRUGO|S_IXUGO;
	inode->i_op = &proc_tgid_base_inode_operations;
	inode->i_fop = &proc_tgid_base_operations;
	inode->i_flags|=S_IMMUTABLE;

	inode->i_nlink = 2 + pid_entry_count_dirs(tgid_base_stuff,
		ARRAY_SIZE(tgid_base_stuff));

	dentry->d_op = &pid_dentry_operations;

	d_add(dentry, inode);
	/* Close the race of the process dying before we return the dentry */
	if (pid_revalidate(dentry, NULL))
		error = NULL;
out:
	return error;
}