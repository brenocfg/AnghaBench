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
struct tty_struct {struct inode* driver_data; } ;
struct super_block {struct dentry* s_root; } ;
struct inode {scalar_t__ i_rdev; int /*<<< orphan*/  i_nlink; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 scalar_t__ MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTMX_MINOR ; 
 int /*<<< orphan*/  TTYAUX_MAJOR ; 
 int /*<<< orphan*/  d_delete (struct dentry*) ; 
 struct dentry* d_find_alias (struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct super_block* pts_sb_from_inode (struct inode*) ; 

void devpts_pty_kill(struct tty_struct *tty)
{
	struct inode *inode = tty->driver_data;
	struct super_block *sb = pts_sb_from_inode(inode);
	struct dentry *root = sb->s_root;
	struct dentry *dentry;

	BUG_ON(inode->i_rdev == MKDEV(TTYAUX_MAJOR, PTMX_MINOR));

	mutex_lock(&root->d_inode->i_mutex);

	dentry = d_find_alias(inode);
	if (IS_ERR(dentry))
		goto out;

	if (dentry) {
		inode->i_nlink--;
		d_delete(dentry);
		dput(dentry);	/* d_alloc_name() in devpts_pty_new() */
	}

	dput(dentry);		/* d_find_alias above */
out:
	mutex_unlock(&root->d_inode->i_mutex);
}