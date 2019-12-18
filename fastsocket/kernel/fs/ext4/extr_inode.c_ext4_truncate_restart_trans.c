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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_data_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/ * EXT4_JOURNAL (struct inode*) ; 
 int /*<<< orphan*/  blocks_for_truncate (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_discard_preallocations (struct inode*) ; 
 int ext4_journal_restart (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ext4_truncate_restart_trans(handle_t *handle, struct inode *inode,
				 int nblocks)
{
	int ret;

	/*
	 * Drop i_data_sem to avoid deadlock with ext4_get_blocks At this
	 * moment, get_block can be called only for blocks inside i_size since
	 * page cache has been already dropped and writes are blocked by
	 * i_mutex. So we can safely drop the i_data_sem here.
	 */
	BUG_ON(EXT4_JOURNAL(inode) == NULL);
	jbd_debug(2, "restarting handle %p\n", handle);
	up_write(&EXT4_I(inode)->i_data_sem);
	ret = ext4_journal_restart(handle, blocks_for_truncate(inode));
	down_write(&EXT4_I(inode)->i_data_sem);
	ext4_discard_preallocations(inode);

	return ret;
}