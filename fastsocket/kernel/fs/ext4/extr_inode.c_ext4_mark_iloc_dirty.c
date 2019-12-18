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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_iloc {int /*<<< orphan*/  bh; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  I_VERSION ; 
 int ext4_do_update_inode (int /*<<< orphan*/ *,struct inode*,struct ext4_iloc*) ; 
 int /*<<< orphan*/  get_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 
 int /*<<< orphan*/  put_bh (int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ext4_mark_iloc_dirty(handle_t *handle,
			 struct inode *inode, struct ext4_iloc *iloc)
{
	int err = 0;

	if (test_opt(inode->i_sb, I_VERSION))
		inode_inc_iversion(inode);

	/* the do_update_inode consumes one bh->b_count */
	get_bh(iloc->bh);

	/* ext4_do_update_inode() does jbd2_journal_dirty_metadata */
	err = ext4_do_update_inode(handle, inode, iloc);
	put_bh(iloc->bh);
	return err;
}