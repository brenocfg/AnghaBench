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
struct dio {scalar_t__ result; scalar_t__ rw; scalar_t__ i_size; scalar_t__ page_errors; scalar_t__ io_error; int flags; TYPE_1__* inode; int /*<<< orphan*/  iocb; int /*<<< orphan*/  private; int /*<<< orphan*/  (* end_io ) (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ;} ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_alloc_sem; } ;

/* Variables and functions */
 int DIO_LOCKING ; 
 scalar_t__ EIOCBQUEUED ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  aio_complete (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  up_read_non_owner (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t dio_complete(struct dio *dio, loff_t offset, ssize_t ret, bool is_async)
{
	ssize_t transferred = 0;

	/*
	 * AIO submission can race with bio completion to get here while
	 * expecting to have the last io completed by bio completion.
	 * In that case -EIOCBQUEUED is in fact not an error we want
	 * to preserve through this call.
	 */
	if (ret == -EIOCBQUEUED)
		ret = 0;

	if (dio->result) {
		transferred = dio->result;

		/* Check for short read case */
		if ((dio->rw == READ) && ((offset + transferred) > dio->i_size))
			transferred = dio->i_size - offset;
	}

	if (ret == 0)
		ret = dio->page_errors;
	if (ret == 0)
		ret = dio->io_error;
	if (ret == 0)
		ret = transferred;

	if (dio->end_io && dio->result) {
		dio->end_io(dio->iocb, offset, transferred,
			    dio->private, ret, is_async);
	} else if (is_async) {
		aio_complete(dio->iocb, ret, 0);
	}

	if (dio->flags & DIO_LOCKING)
		/* lockdep: non-owner release */
		up_read_non_owner(&dio->inode->i_alloc_sem);

	return ret;
}