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
struct kiocb {struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct iov_iter {int dummy; } ;
struct file {int f_flags; struct address_space* f_mapping; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int O_DIRECT ; 
 scalar_t__ filemap_write_and_wait_range (struct address_space*,scalar_t__,scalar_t__) ; 
 scalar_t__ generic_perform_write (struct file*,struct iov_iter*,scalar_t__) ; 
 int /*<<< orphan*/  iov_iter_init (struct iov_iter*,struct iovec const*,unsigned long,size_t,scalar_t__) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

ssize_t
generic_file_buffered_write(struct kiocb *iocb, const struct iovec *iov,
		unsigned long nr_segs, loff_t pos, loff_t *ppos,
		size_t count, ssize_t written)
{
	struct file *file = iocb->ki_filp;
	struct address_space *mapping = file->f_mapping;
	ssize_t status;
	struct iov_iter i;

	iov_iter_init(&i, iov, nr_segs, count, written);
	status = generic_perform_write(file, &i, pos);

	if (likely(status >= 0)) {
		written += status;
		*ppos = pos + status;
  	}
	
	/*
	 * If we get here for O_DIRECT writes then we must have fallen through
	 * to buffered writes (block instantiation inside i_size).  So we sync
	 * the file data here, to try to honour O_DIRECT expectations.
	 */
	if (unlikely(file->f_flags & O_DIRECT) && written)
		status = filemap_write_and_wait_range(mapping,
					pos, pos + written - 1);

	return written ? written : status;
}