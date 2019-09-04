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
struct aiocb {scalar_t__ __err; } ;

/* Variables and functions */
 int AIO_ALLDONE ; 
 int AIO_NOTCANCELED ; 
 scalar_t__ EINPROGRESS ; 

int aio_cancel(int fd, struct aiocb *cb)
{
	if (!cb) {
		/* FIXME: for correctness, we should return AIO_ALLDONE
		 * if there are no outstanding aio operations on this
		 * file descriptor, but that would require making aio
		 * much slower, and seems to have little advantage since
		 * we don't support cancellation anyway. */
		return AIO_NOTCANCELED;
	}
	return cb->__err==EINPROGRESS ? AIO_NOTCANCELED : AIO_ALLDONE;
}