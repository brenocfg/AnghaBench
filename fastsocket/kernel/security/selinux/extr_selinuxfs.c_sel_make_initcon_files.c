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
struct inode {int i_ino; int /*<<< orphan*/ * i_fop; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SECINITSID_NUM ; 
 int SEL_INITCON_INO_OFFSET ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_get_initial_sid_context (int) ; 
 int /*<<< orphan*/  sel_initcon_ops ; 
 struct inode* sel_make_inode (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sel_make_initcon_files(struct dentry *dir)
{
	int i, ret = 0;

	for (i = 1; i <= SECINITSID_NUM; i++) {
		struct inode *inode;
		struct dentry *dentry;
		dentry = d_alloc_name(dir, security_get_initial_sid_context(i));
		if (!dentry) {
			ret = -ENOMEM;
			goto out;
		}

		inode = sel_make_inode(dir->d_sb, S_IFREG|S_IRUGO);
		if (!inode) {
			ret = -ENOMEM;
			goto out;
		}
		inode->i_fop = &sel_initcon_ops;
		inode->i_ino = i|SEL_INITCON_INO_OFFSET;
		d_add(dentry, inode);
	}
out:
	return ret;
}