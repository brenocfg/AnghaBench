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
struct TYPE_2__ {int /*<<< orphan*/  truncate_mutex; } ;

/* Variables and functions */
 TYPE_1__* EXT3_I (struct inode*) ; 
 int /*<<< orphan*/  blocks_for_truncate (struct inode*) ; 
 int ext3_journal_restart (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int truncate_restart_transaction(handle_t *handle, struct inode *inode)
{
	int ret;

	jbd_debug(2, "restarting handle %p\n", handle);
	/*
	 * Drop truncate_mutex to avoid deadlock with ext3_get_blocks_handle
	 * At this moment, get_block can be called only for blocks inside
	 * i_size since page cache has been already dropped and writes are
	 * blocked by i_mutex. So we can safely drop the truncate_mutex.
	 */
	mutex_unlock(&EXT3_I(inode)->truncate_mutex);
	ret = ext3_journal_restart(handle, blocks_for_truncate(inode));
	mutex_lock(&EXT3_I(inode)->truncate_mutex);
	return ret;
}