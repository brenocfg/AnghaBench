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
struct ubifs_inode {scalar_t__ del_cmtno; } ;
struct ubifs_info {scalar_t__ cmt_no; int /*<<< orphan*/  commit_sem; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_delete_orphan (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 struct ubifs_inode* ubifs_inode (struct inode const*) ; 
 int ubifs_jnl_write_inode (struct ubifs_info*,struct inode const*) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int) ; 
 int ubifs_tnc_remove_ino (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ubifs_jnl_delete_inode(struct ubifs_info *c, const struct inode *inode)
{
	int err;
	struct ubifs_inode *ui = ubifs_inode(inode);

	ubifs_assert(inode->i_nlink == 0);

	if (ui->del_cmtno != c->cmt_no)
		/* A commit happened for sure */
		return ubifs_jnl_write_inode(c, inode);

	down_read(&c->commit_sem);
	/*
	 * Check commit number again, because the first test has been done
	 * without @c->commit_sem, so a commit might have happened.
	 */
	if (ui->del_cmtno != c->cmt_no) {
		up_read(&c->commit_sem);
		return ubifs_jnl_write_inode(c, inode);
	}

	err = ubifs_tnc_remove_ino(c, inode->i_ino);
	if (err)
		ubifs_ro_mode(c, err);
	else
		ubifs_delete_orphan(c, inode->i_ino);
	up_read(&c->commit_sem);
	return err;
}