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
struct kiocb {int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EIOCBQUEUED ; 
 scalar_t__ __generic_file_aio_write (struct kiocb*,struct iovec const*,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ generic_write_sync (struct file*,int /*<<< orphan*/ ,scalar_t__) ; 

ssize_t blkdev_aio_write(struct kiocb *iocb, const struct iovec *iov,
			 unsigned long nr_segs, loff_t pos)
{
	struct file *file = iocb->ki_filp;
	ssize_t ret;

	BUG_ON(iocb->ki_pos != pos);
	ret = __generic_file_aio_write(iocb, iov, nr_segs, &iocb->ki_pos);
	if (ret > 0 || ret == -EIOCBQUEUED) {
		ssize_t err;

		err = generic_write_sync(file, pos, ret);
		if (err < 0 && ret > 0)
			ret = err;
	}
	return ret;
}