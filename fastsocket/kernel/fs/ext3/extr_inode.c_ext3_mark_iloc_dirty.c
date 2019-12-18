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
struct inode {int dummy; } ;
struct ext3_iloc {int /*<<< orphan*/  bh; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ext3_do_update_inode (int /*<<< orphan*/ *,struct inode*,struct ext3_iloc*) ; 
 int /*<<< orphan*/  get_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bh (int /*<<< orphan*/ ) ; 

int ext3_mark_iloc_dirty(handle_t *handle,
		struct inode *inode, struct ext3_iloc *iloc)
{
	int err = 0;

	/* the do_update_inode consumes one bh->b_count */
	get_bh(iloc->bh);

	/* ext3_do_update_inode() does journal_dirty_metadata */
	err = ext3_do_update_inode(handle, inode, iloc);
	put_bh(iloc->bh);
	return err;
}