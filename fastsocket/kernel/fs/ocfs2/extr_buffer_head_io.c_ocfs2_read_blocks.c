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
typedef  scalar_t__ u64 ;
typedef  struct super_block super_block ;
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_end_io; scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  ML_BH_IO ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  ML_UPTODATE ; 
 int OCFS2_BH_IGNORE_CACHE ; 
 int OCFS2_BH_READAHEAD ; 
 int /*<<< orphan*/  READ ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int buffer_jbd (struct buffer_head*) ; 
 scalar_t__ buffer_needs_validate (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_needs_validate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct ocfs2_caching_info*,unsigned long long,int,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 scalar_t__ ocfs2_buffer_read_ahead (struct ocfs2_caching_info*,struct buffer_head*) ; 
 scalar_t__ ocfs2_buffer_uptodate (struct ocfs2_caching_info*,struct buffer_head*) ; 
 struct super_block* ocfs2_metadata_cache_get_super (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_io_lock (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_io_unlock (struct ocfs2_caching_info*) ; 
 scalar_t__ ocfs2_metadata_cache_owner (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_set_buffer_uptodate (struct ocfs2_caching_info*,struct buffer_head*) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 struct buffer_head* sb_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_needs_validate (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int ocfs2_read_blocks(struct ocfs2_caching_info *ci, u64 block, int nr,
		      struct buffer_head *bhs[], int flags,
		      int (*validate)(struct super_block *sb,
				      struct buffer_head *bh))
{
	int status = 0;
	int i, ignore_cache = 0;
	struct buffer_head *bh;
	struct super_block *sb = ocfs2_metadata_cache_get_super(ci);

	mlog_entry("(ci=%p, block=(%llu), nr=(%d), flags=%d)\n",
		   ci, (unsigned long long)block, nr, flags);

	BUG_ON(!ci);
	BUG_ON((flags & OCFS2_BH_READAHEAD) &&
	       (flags & OCFS2_BH_IGNORE_CACHE));

	if (bhs == NULL) {
		status = -EINVAL;
		mlog_errno(status);
		goto bail;
	}

	if (nr < 0) {
		mlog(ML_ERROR, "asked to read %d blocks!\n", nr);
		status = -EINVAL;
		mlog_errno(status);
		goto bail;
	}

	if (nr == 0) {
		mlog(ML_BH_IO, "No buffers will be read!\n");
		status = 0;
		goto bail;
	}

	ocfs2_metadata_cache_io_lock(ci);
	for (i = 0 ; i < nr ; i++) {
		if (bhs[i] == NULL) {
			bhs[i] = sb_getblk(sb, block++);
			if (bhs[i] == NULL) {
				ocfs2_metadata_cache_io_unlock(ci);
				status = -EIO;
				mlog_errno(status);
				goto bail;
			}
		}
		bh = bhs[i];
		ignore_cache = (flags & OCFS2_BH_IGNORE_CACHE);

		/* There are three read-ahead cases here which we need to
		 * be concerned with. All three assume a buffer has
		 * previously been submitted with OCFS2_BH_READAHEAD
		 * and it hasn't yet completed I/O.
		 *
		 * 1) The current request is sync to disk. This rarely
		 *    happens these days, and never when performance
		 *    matters - the code can just wait on the buffer
		 *    lock and re-submit.
		 *
		 * 2) The current request is cached, but not
		 *    readahead. ocfs2_buffer_uptodate() will return
		 *    false anyway, so we'll wind up waiting on the
		 *    buffer lock to do I/O. We re-check the request
		 *    with after getting the lock to avoid a re-submit.
		 *
		 * 3) The current request is readahead (and so must
		 *    also be a caching one). We short circuit if the
		 *    buffer is locked (under I/O) and if it's in the
		 *    uptodate cache. The re-check from #2 catches the
		 *    case that the previous read-ahead completes just
		 *    before our is-it-in-flight check.
		 */

		if (!ignore_cache && !ocfs2_buffer_uptodate(ci, bh)) {
			mlog(ML_UPTODATE,
			     "bh (%llu), owner %llu not uptodate\n",
			     (unsigned long long)bh->b_blocknr,
			     (unsigned long long)ocfs2_metadata_cache_owner(ci));
			/* We're using ignore_cache here to say
			 * "go to disk" */
			ignore_cache = 1;
		}

		if (buffer_jbd(bh)) {
			if (ignore_cache)
				mlog(ML_BH_IO, "trying to sync read a jbd "
					       "managed bh (blocknr = %llu)\n",
				     (unsigned long long)bh->b_blocknr);
			continue;
		}

		if (ignore_cache) {
			if (buffer_dirty(bh)) {
				/* This should probably be a BUG, or
				 * at least return an error. */
				mlog(ML_BH_IO, "asking me to sync read a dirty "
					       "buffer! (blocknr = %llu)\n",
				     (unsigned long long)bh->b_blocknr);
				continue;
			}

			/* A read-ahead request was made - if the
			 * buffer is already under read-ahead from a
			 * previously submitted request than we are
			 * done here. */
			if ((flags & OCFS2_BH_READAHEAD)
			    && ocfs2_buffer_read_ahead(ci, bh))
				continue;

			lock_buffer(bh);
			if (buffer_jbd(bh)) {
#ifdef CATCH_BH_JBD_RACES
				mlog(ML_ERROR, "block %llu had the JBD bit set "
					       "while I was in lock_buffer!",
				     (unsigned long long)bh->b_blocknr);
				BUG();
#else
				unlock_buffer(bh);
				continue;
#endif
			}

			/* Re-check ocfs2_buffer_uptodate() as a
			 * previously read-ahead buffer may have
			 * completed I/O while we were waiting for the
			 * buffer lock. */
			if (!(flags & OCFS2_BH_IGNORE_CACHE)
			    && !(flags & OCFS2_BH_READAHEAD)
			    && ocfs2_buffer_uptodate(ci, bh)) {
				unlock_buffer(bh);
				continue;
			}

			clear_buffer_uptodate(bh);
			get_bh(bh); /* for end_buffer_read_sync() */
			if (validate)
				set_buffer_needs_validate(bh);
			bh->b_end_io = end_buffer_read_sync;
			submit_bh(READ, bh);
			continue;
		}
	}

	status = 0;

	for (i = (nr - 1); i >= 0; i--) {
		bh = bhs[i];

		if (!(flags & OCFS2_BH_READAHEAD)) {
			/* We know this can't have changed as we hold the
			 * owner sem. Avoid doing any work on the bh if the
			 * journal has it. */
			if (!buffer_jbd(bh))
				wait_on_buffer(bh);

			if (!buffer_uptodate(bh)) {
				/* Status won't be cleared from here on out,
				 * so we can safely record this and loop back
				 * to cleanup the other buffers. Don't need to
				 * remove the clustered uptodate information
				 * for this bh as it's not marked locally
				 * uptodate. */
				status = -EIO;
				put_bh(bh);
				bhs[i] = NULL;
				continue;
			}

			if (buffer_needs_validate(bh)) {
				/* We never set NeedsValidate if the
				 * buffer was held by the journal, so
				 * that better not have changed */
				BUG_ON(buffer_jbd(bh));
				clear_buffer_needs_validate(bh);
				status = validate(sb, bh);
				if (status) {
					put_bh(bh);
					bhs[i] = NULL;
					continue;
				}
			}
		}

		/* Always set the buffer in the cache, even if it was
		 * a forced read, or read-ahead which hasn't yet
		 * completed. */
		ocfs2_set_buffer_uptodate(ci, bh);
	}
	ocfs2_metadata_cache_io_unlock(ci);

	mlog(ML_BH_IO, "block=(%llu), nr=(%d), cached=%s, flags=0x%x\n", 
	     (unsigned long long)block, nr,
	     ((flags & OCFS2_BH_IGNORE_CACHE) || ignore_cache) ? "no" : "yes",
	     flags);

bail:

	mlog_exit(status);
	return status;
}