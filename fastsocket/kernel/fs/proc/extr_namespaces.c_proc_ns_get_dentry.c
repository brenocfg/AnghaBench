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
struct qstr {char* name; } ;
struct proc_ns_operations {int /*<<< orphan*/  (* put ) (void*) ;int /*<<< orphan*/  (* inum ) (void*) ;void* (* get ) (struct task_struct*) ;} ;
struct proc_inode {void* ns; struct proc_ns_operations const* ns_ops; } ;
struct inode {int i_state; int i_mode; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; } ;
struct dentry {int /*<<< orphan*/ * d_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int I_NEW ; 
 struct proc_inode* PROC_I (struct inode*) ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 struct dentry* d_alloc_pseudo (struct super_block*,struct qstr*) ; 
 struct dentry* d_instantiate_unique (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct inode* iget_locked (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_dentry_operations ; 
 int /*<<< orphan*/  ns_file_operations ; 
 int /*<<< orphan*/  ns_inode_operations ; 
 void* stub1 (struct task_struct*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  stub3 (void*) ; 
 int /*<<< orphan*/  stub4 (void*) ; 
 int /*<<< orphan*/  stub5 (void*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static struct dentry *proc_ns_get_dentry(struct super_block *sb,
	struct task_struct *task, const struct proc_ns_operations *ns_ops)
{
	struct dentry *dentry, *result;
	struct inode *inode;
	struct proc_inode *ei;
	struct qstr qname = { .name = "", };
	void *ns;

	ns = ns_ops->get(task);
	if (!ns)
		return ERR_PTR(-ENOENT);

	dentry = d_alloc_pseudo(sb, &qname);
	if (!dentry) {
		ns_ops->put(ns);
		return ERR_PTR(-ENOMEM);
	}

	inode = iget_locked(sb, ns_ops->inum(ns));
	if (!inode) {
		dput(dentry);
		ns_ops->put(ns);
		return ERR_PTR(-ENOMEM);
	}

	ei = PROC_I(inode);
	if (inode->i_state & I_NEW) {
		inode->i_mtime = inode->i_atime = inode->i_ctime = CURRENT_TIME;
		inode->i_op = &ns_inode_operations;
		inode->i_mode = S_IFREG | S_IRUGO;
		inode->i_fop = &ns_file_operations;
		ei->ns_ops = ns_ops;
		ei->ns = ns;
		unlock_new_inode(inode);
	} else {
		ns_ops->put(ns);
	}

	dentry->d_op = &ns_dentry_operations;
	result = d_instantiate_unique(dentry, inode);
	if (result) {
		dput(dentry);
		dentry = result;
	}

	return dentry;
}