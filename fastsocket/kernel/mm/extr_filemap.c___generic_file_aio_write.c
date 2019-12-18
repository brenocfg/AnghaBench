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
struct kiocb {struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
struct file {int f_flags; struct address_space* f_mapping; } ;
struct address_space {int /*<<< orphan*/ * backing_dev_info; struct inode* host; } ;
typedef  size_t ssize_t ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/ * backing_dev_info; } ;

/* Variables and functions */
 int O_DIRECT ; 
 int PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  SB_FREEZE_WRITE ; 
 int SYNC_FILE_RANGE_WAIT_AFTER ; 
 int SYNC_FILE_RANGE_WAIT_BEFORE ; 
 int SYNC_FILE_RANGE_WRITE ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY_READ ; 
 TYPE_1__* current ; 
 size_t do_sync_mapping_range (struct address_space*,int,int,int) ; 
 size_t file_remove_suid (struct file*) ; 
 int /*<<< orphan*/  file_update_time (struct file*) ; 
 size_t generic_file_buffered_write (struct kiocb*,struct iovec const*,unsigned long,int,int*,size_t,size_t) ; 
 size_t generic_file_direct_write (struct kiocb*,struct iovec const*,unsigned long*,int,int*,size_t,size_t) ; 
 size_t generic_segment_checks (struct iovec const*,unsigned long*,size_t*,int /*<<< orphan*/ ) ; 
 size_t generic_write_checks (struct file*,int*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (struct address_space*,int,int) ; 
 int /*<<< orphan*/  sb_has_new_freeze (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vfs_check_frozen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ssize_t __generic_file_aio_write(struct kiocb *iocb, const struct iovec *iov,
				 unsigned long nr_segs, loff_t *ppos)
{
	struct file *file = iocb->ki_filp;
	struct address_space * mapping = file->f_mapping;
	size_t ocount;		/* original count */
	size_t count;		/* after file limit checks */
	struct inode 	*inode = mapping->host;
	loff_t		pos;
	ssize_t		written;
	ssize_t		err;

	ocount = 0;
	err = generic_segment_checks(iov, &nr_segs, &ocount, VERIFY_READ);
	if (err)
		return err;

	count = ocount;
	pos = *ppos;

	if (!sb_has_new_freeze(inode->i_sb))
		vfs_check_frozen(inode->i_sb, SB_FREEZE_WRITE);

	/* We can write back this queue in page reclaim */
	current->backing_dev_info = mapping->backing_dev_info;
	written = 0;

	err = generic_write_checks(file, &pos, &count, S_ISBLK(inode->i_mode));
	if (err)
		goto out;

	if (count == 0)
		goto out;

	err = file_remove_suid(file);
	if (err)
		goto out;

	file_update_time(file);

	/* coalesce the iovecs and go direct-to-BIO for O_DIRECT */
	if (unlikely(file->f_flags & O_DIRECT)) {
		loff_t endbyte;
		ssize_t written_buffered;

		written = generic_file_direct_write(iocb, iov, &nr_segs, pos,
							ppos, count, ocount);
		if (written < 0 || written == count)
			goto out;
		/*
		 * direct-io write to a hole: fall through to buffered I/O
		 * for completing the rest of the request.
		 */
		pos += written;
		count -= written;
		written_buffered = generic_file_buffered_write(iocb, iov,
						nr_segs, pos, ppos, count,
						written);
		/*
		 * If generic_file_buffered_write() retuned a synchronous error
		 * then we want to return the number of bytes which were
		 * direct-written, or the error code if that was zero.  Note
		 * that this differs from normal direct-io semantics, which
		 * will return -EFOO even if some bytes were written.
		 */
		if (written_buffered < 0) {
			err = written_buffered;
			goto out;
		}

		/*
		 * We need to ensure that the page cache pages are written to
		 * disk and invalidated to preserve the expected O_DIRECT
		 * semantics.
		 */
		endbyte = pos + written_buffered - written - 1;
		err = do_sync_mapping_range(file->f_mapping, pos, endbyte,
					    SYNC_FILE_RANGE_WAIT_BEFORE|
					    SYNC_FILE_RANGE_WRITE|
					    SYNC_FILE_RANGE_WAIT_AFTER);
		if (err == 0) {
			written = written_buffered;
			invalidate_mapping_pages(mapping,
						 pos >> PAGE_CACHE_SHIFT,
						 endbyte >> PAGE_CACHE_SHIFT);
		} else {
			/*
			 * We don't know how much we wrote, so just return
			 * the number of bytes which were direct-written
			 */
		}
	} else {
		written = generic_file_buffered_write(iocb, iov, nr_segs,
				pos, ppos, count, written);
	}
out:
	current->backing_dev_info = NULL;
	return written ? written : err;
}