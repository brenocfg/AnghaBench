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
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_freed (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 

__attribute__((used)) static int do_journal_get_write_access(handle_t *handle,
				       struct buffer_head *bh)
{
	int dirty = buffer_dirty(bh);
	int ret;

	if (!buffer_mapped(bh) || buffer_freed(bh))
		return 0;
	/*
	 * __block_prepare_write() could have dirtied some buffers. Clean
	 * the dirty bit as jbd2_journal_get_write_access() could complain
	 * otherwise about fs integrity issues. Setting of the dirty bit
	 * by __block_prepare_write() isn't a real problem here as we clear
	 * the bit before releasing a page lock and thus writeback cannot
	 * ever write the buffer.
	 */
	if (dirty)
		clear_buffer_dirty(bh);
	ret = ext4_journal_get_write_access(handle, bh);
	if (!ret && dirty)
		ret = ext4_handle_dirty_metadata(handle, NULL, bh);
	return ret;
}