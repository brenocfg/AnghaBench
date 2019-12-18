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
struct ext3_iloc {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 int ext3_mark_iloc_dirty (int /*<<< orphan*/ *,struct inode*,struct ext3_iloc*) ; 
 int ext3_reserve_inode_write (int /*<<< orphan*/ *,struct inode*,struct ext3_iloc*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  trace_ext3_mark_inode_dirty (struct inode*,int /*<<< orphan*/ ) ; 

int ext3_mark_inode_dirty(handle_t *handle, struct inode *inode)
{
	struct ext3_iloc iloc;
	int err;

	might_sleep();
	trace_ext3_mark_inode_dirty(inode, _RET_IP_);
	err = ext3_reserve_inode_write(handle, inode, &iloc);
	if (!err)
		err = ext3_mark_iloc_dirty(handle, inode, &iloc);
	return err;
}