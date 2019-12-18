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
struct qstr {int dummy; } ;
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/ * d_op; struct qstr d_name; } ;
struct ctl_table_header {struct ctl_table* attached_by; struct ctl_table* attached_to; struct ctl_table* ctl_table; } ;
struct ctl_table {struct ctl_table* child; } ;
struct TYPE_2__ {struct ctl_table* sysctl_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_CAST (struct ctl_table_header*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct ctl_table_header*) ; 
 TYPE_1__* PROC_I (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct ctl_table* find_in_table (struct ctl_table*,struct qstr*) ; 
 struct ctl_table_header* grab_header (struct inode*) ; 
 int /*<<< orphan*/  proc_sys_dentry_operations ; 
 struct inode* proc_sys_make_inode (int /*<<< orphan*/ ,struct ctl_table_header*,struct ctl_table*) ; 
 int /*<<< orphan*/  sysctl_head_finish (struct ctl_table_header*) ; 
 struct ctl_table_header* sysctl_head_next (struct ctl_table_header*) ; 

__attribute__((used)) static struct dentry *proc_sys_lookup(struct inode *dir, struct dentry *dentry,
					struct nameidata *nd)
{
	struct ctl_table_header *head = grab_header(dir);
	struct ctl_table *table = PROC_I(dir)->sysctl_entry;
	struct ctl_table_header *h = NULL;
	struct qstr *name = &dentry->d_name;
	struct ctl_table *p;
	struct inode *inode;
	struct dentry *err = ERR_PTR(-ENOENT);

	if (IS_ERR(head))
		return ERR_CAST(head);

	if (table && !table->child) {
		WARN_ON(1);
		goto out;
	}

	table = table ? table->child : head->ctl_table;

	p = find_in_table(table, name);
	if (!p) {
		for (h = sysctl_head_next(NULL); h; h = sysctl_head_next(h)) {
			if (h->attached_to != table)
				continue;
			p = find_in_table(h->attached_by, name);
			if (p)
				break;
		}
	}

	if (!p)
		goto out;

	err = ERR_PTR(-ENOMEM);
	inode = proc_sys_make_inode(dir->i_sb, h ? h : head, p);
	if (h)
		sysctl_head_finish(h);

	if (!inode)
		goto out;

	err = NULL;
	dentry->d_op = &proc_sys_dentry_operations;
	d_add(dentry, inode);

out:
	sysctl_head_finish(head);
	return err;
}