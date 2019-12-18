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
struct ocfs2_super {int dummy; } ;
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {scalar_t__ b_blocknr; int /*<<< orphan*/  b_end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int EROFS ; 
 scalar_t__ OCFS2_SUPER_BLOCK_BLKNO ; 
 int /*<<< orphan*/  WRITE ; 
 int buffer_jbd (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_write_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_entry (char*,unsigned long long,struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 scalar_t__ ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_io_lock (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_io_unlock (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_set_buffer_uptodate (struct ocfs2_caching_info*,struct buffer_head*) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int ocfs2_write_block(struct ocfs2_super *osb, struct buffer_head *bh,
		      struct ocfs2_caching_info *ci)
{
	int ret = 0;

	mlog_entry("(bh->b_blocknr = %llu, ci=%p)\n",
		   (unsigned long long)bh->b_blocknr, ci);

	BUG_ON(bh->b_blocknr < OCFS2_SUPER_BLOCK_BLKNO);
	BUG_ON(buffer_jbd(bh));

	/* No need to check for a soft readonly file system here. non
	 * journalled writes are only ever done on system files which
	 * can get modified during recovery even if read-only. */
	if (ocfs2_is_hard_readonly(osb)) {
		ret = -EROFS;
		goto out;
	}

	ocfs2_metadata_cache_io_lock(ci);

	lock_buffer(bh);
	set_buffer_uptodate(bh);

	/* remove from dirty list before I/O. */
	clear_buffer_dirty(bh);

	get_bh(bh); /* for end_buffer_write_sync() */
	bh->b_end_io = end_buffer_write_sync;
	submit_bh(WRITE, bh);

	wait_on_buffer(bh);

	if (buffer_uptodate(bh)) {
		ocfs2_set_buffer_uptodate(ci, bh);
	} else {
		/* We don't need to remove the clustered uptodate
		 * information for this bh as it's not marked locally
		 * uptodate. */
		ret = -EIO;
		put_bh(bh);
	}

	ocfs2_metadata_cache_io_unlock(ci);
out:
	mlog_exit(ret);
	return ret;
}