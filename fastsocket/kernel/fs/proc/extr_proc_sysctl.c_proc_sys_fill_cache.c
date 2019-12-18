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
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {int /*<<< orphan*/  f_pos; TYPE_1__ f_path; } ;
struct dentry {struct inode* d_inode; int /*<<< orphan*/ * d_op; int /*<<< orphan*/  d_sb; } ;
struct ctl_table_header {int dummy; } ;
struct ctl_table {int /*<<< orphan*/  procname; } ;
typedef  int /*<<< orphan*/  ino_t ;
typedef  int /*<<< orphan*/  (* filldir_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;

/* Variables and functions */
 unsigned int DT_UNKNOWN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc (struct dentry*,struct qstr*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  full_name_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_sys_dentry_operations ; 
 struct inode* proc_sys_make_inode (int /*<<< orphan*/ ,struct ctl_table_header*,struct ctl_table*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_sys_fill_cache(struct file *filp, void *dirent,
				filldir_t filldir,
				struct ctl_table_header *head,
				struct ctl_table *table)
{
	struct dentry *child, *dir = filp->f_path.dentry;
	struct inode *inode;
	struct qstr qname;
	ino_t ino = 0;
	unsigned type = DT_UNKNOWN;

	qname.name = table->procname;
	qname.len  = strlen(table->procname);
	qname.hash = full_name_hash(qname.name, qname.len);

	child = d_lookup(dir, &qname);
	if (!child) {
		child = d_alloc(dir, &qname);
		if (child) {
			inode = proc_sys_make_inode(dir->d_sb, head, table);
			if (!inode) {
				dput(child);
				return -ENOMEM;
			} else {
				child->d_op = &proc_sys_dentry_operations;
				d_add(child, inode);
			}
		} else {
			return -ENOMEM;
		}
	}
	inode = child->d_inode;
	ino  = inode->i_ino;
	type = inode->i_mode >> 12;
	dput(child);
	return !!filldir(dirent, qname.name, qname.len, filp->f_pos, ino, type);
}