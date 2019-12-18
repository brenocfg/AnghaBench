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
struct kiocb {size_t ki_pos; struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct iov_iter {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mutex; int /*<<< orphan*/  i_mode; } ;
struct file {int f_flags; struct address_space* f_mapping; } ;
struct address_space {int /*<<< orphan*/ * backing_dev_info; struct inode* host; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;
struct TYPE_2__ {int /*<<< orphan*/ * backing_dev_info; } ;

/* Variables and functions */
 int O_DIRECT ; 
 size_t PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY_READ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* current ; 
 size_t file_remove_suid (struct file*) ; 
 int /*<<< orphan*/  file_update_time (struct file*) ; 
 size_t filemap_write_and_wait_range (struct address_space*,size_t,size_t) ; 
 size_t fuse_perform_write (struct file*,struct address_space*,struct iov_iter*,size_t) ; 
 size_t generic_file_direct_write (struct kiocb*,struct iovec const*,unsigned long*,size_t,size_t*,size_t,size_t) ; 
 size_t generic_segment_checks (struct iovec const*,unsigned long*,size_t*,int /*<<< orphan*/ ) ; 
 size_t generic_write_checks (struct file*,size_t*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (struct address_space*,size_t,size_t) ; 
 int /*<<< orphan*/  iov_iter_init (struct iov_iter*,struct iovec const*,unsigned long,size_t,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sb_end_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t fuse_file_aio_write(struct kiocb *iocb, const struct iovec *iov,
				   unsigned long nr_segs, loff_t pos)
{
	struct file *file = iocb->ki_filp;
	struct address_space *mapping = file->f_mapping;
	size_t count = 0;
	size_t ocount = 0;
	ssize_t written = 0;
	ssize_t written_buffered = 0;
	struct inode *inode = mapping->host;
	ssize_t err;
	struct iov_iter i;
	loff_t endbyte = 0;

	WARN_ON(iocb->ki_pos != pos);

	ocount = 0;
	err = generic_segment_checks(iov, &nr_segs, &ocount, VERIFY_READ);
	if (err)
		return err;

	count = ocount;
	sb_start_write(inode->i_sb);
	mutex_lock(&inode->i_mutex);

	/* We can write back this queue in page reclaim */
	current->backing_dev_info = mapping->backing_dev_info;

	err = generic_write_checks(file, &pos, &count, S_ISBLK(inode->i_mode));
	if (err)
		goto out;

	if (count == 0)
		goto out;

	err = file_remove_suid(file);
	if (err)
		goto out;

	file_update_time(file);

	if (file->f_flags & O_DIRECT) {
		written = generic_file_direct_write(iocb, iov, &nr_segs,
						    pos, &iocb->ki_pos,
						    count, ocount);
		if (written < 0 || written == count)
			goto out;

		pos += written;
		count -= written;

		iov_iter_init(&i, iov, nr_segs, count, written);
		written_buffered = fuse_perform_write(file, mapping, &i, pos);
		if (written_buffered < 0) {
			err = written_buffered;
			goto out;
		}
		endbyte = pos + written_buffered - 1;

		err = filemap_write_and_wait_range(file->f_mapping, pos,
						   endbyte);
		if (err)
			goto out;

		invalidate_mapping_pages(file->f_mapping,
					 pos >> PAGE_CACHE_SHIFT,
					 endbyte >> PAGE_CACHE_SHIFT);

		written += written_buffered;
		iocb->ki_pos = pos + written_buffered;
	} else {
		iov_iter_init(&i, iov, nr_segs, count, 0);
		written = fuse_perform_write(file, mapping, &i, pos);
		if (written >= 0)
			iocb->ki_pos = pos + written;
	}
out:
	current->backing_dev_info = NULL;
	mutex_unlock(&inode->i_mutex);
	sb_end_write(inode->i_sb);

	return written ? written : err;
}