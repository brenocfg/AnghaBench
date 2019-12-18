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
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/ * i_fop; } ;
struct dentry {int /*<<< orphan*/  d_inode; int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,char*) ; 
 int /*<<< orphan*/  last_class_ino ; 
 int /*<<< orphan*/  sel_class_ops ; 
 int /*<<< orphan*/  sel_class_to_ino (int) ; 
 int sel_make_dir (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 
 struct inode* sel_make_inode (int /*<<< orphan*/ ,int) ; 
 int sel_make_perm_files (char*,int,struct dentry*) ; 

__attribute__((used)) static int sel_make_class_dir_entries(char *classname, int index,
					struct dentry *dir)
{
	struct dentry *dentry = NULL;
	struct inode *inode = NULL;
	int rc;

	dentry = d_alloc_name(dir, "index");
	if (!dentry) {
		rc = -ENOMEM;
		goto out;
	}

	inode = sel_make_inode(dir->d_sb, S_IFREG|S_IRUGO);
	if (!inode) {
		rc = -ENOMEM;
		goto out;
	}

	inode->i_fop = &sel_class_ops;
	inode->i_ino = sel_class_to_ino(index);
	d_add(dentry, inode);

	dentry = d_alloc_name(dir, "perms");
	if (!dentry) {
		rc = -ENOMEM;
		goto out;
	}

	rc = sel_make_dir(dir->d_inode, dentry, &last_class_ino);
	if (rc)
		goto out;

	rc = sel_make_perm_files(classname, index, dentry);

out:
	return rc;
}