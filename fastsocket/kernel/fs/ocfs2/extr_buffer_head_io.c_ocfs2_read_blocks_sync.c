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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct buffer_head {int /*<<< orphan*/  b_end_io; scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EIO ; 
 int /*<<< orphan*/  ML_BH_IO ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  READ ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_jbd (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int ocfs2_read_blocks_sync(struct ocfs2_super *osb, u64 block,
			   unsigned int nr, struct buffer_head *bhs[])
{
	int status = 0;
	unsigned int i;
	struct buffer_head *bh;

	if (!nr) {
		mlog(ML_BH_IO, "No buffers will be read!\n");
		goto bail;
	}

	for (i = 0 ; i < nr ; i++) {
		if (bhs[i] == NULL) {
			bhs[i] = sb_getblk(osb->sb, block++);
			if (bhs[i] == NULL) {
				status = -EIO;
				mlog_errno(status);
				goto bail;
			}
		}
		bh = bhs[i];

		if (buffer_jbd(bh)) {
			mlog(ML_BH_IO,
			     "trying to sync read a jbd "
			     "managed bh (blocknr = %llu), skipping\n",
			     (unsigned long long)bh->b_blocknr);
			continue;
		}

		if (buffer_dirty(bh)) {
			/* This should probably be a BUG, or
			 * at least return an error. */
			mlog(ML_ERROR,
			     "trying to sync read a dirty "
			     "buffer! (blocknr = %llu), skipping\n",
			     (unsigned long long)bh->b_blocknr);
			continue;
		}

		lock_buffer(bh);
		if (buffer_jbd(bh)) {
			mlog(ML_ERROR,
			     "block %llu had the JBD bit set "
			     "while I was in lock_buffer!",
			     (unsigned long long)bh->b_blocknr);
			BUG();
		}

		clear_buffer_uptodate(bh);
		get_bh(bh); /* for end_buffer_read_sync() */
		bh->b_end_io = end_buffer_read_sync;
		submit_bh(READ, bh);
	}

	for (i = nr; i > 0; i--) {
		bh = bhs[i - 1];

		/* No need to wait on the buffer if it's managed by JBD. */
		if (!buffer_jbd(bh))
			wait_on_buffer(bh);

		if (!buffer_uptodate(bh)) {
			/* Status won't be cleared from here on out,
			 * so we can safely record this and loop back
			 * to cleanup the other buffers. */
			status = -EIO;
			put_bh(bh);
			bhs[i - 1] = NULL;
		}
	}

bail:
	return status;
}