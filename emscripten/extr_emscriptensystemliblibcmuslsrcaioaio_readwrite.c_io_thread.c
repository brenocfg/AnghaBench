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
struct sigevent {int sigev_notify; int /*<<< orphan*/  sigev_value; int /*<<< orphan*/  (* sigev_notify_function ) (int /*<<< orphan*/ ) ;} ;
struct aiocb {int aio_fildes; size_t aio_nbytes; int aio_lio_opcode; int /*<<< orphan*/  __err; scalar_t__ __ret; struct sigevent aio_sigevent; int /*<<< orphan*/  aio_offset; scalar_t__ aio_buf; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ ESPIPE ; 
 int /*<<< orphan*/  F_GETFL ; 
 int LIO_READ ; 
 int LIO_WRITE ; 
 int O_APPEND ; 
#define  SIGEV_SIGNAL 129 
#define  SIGEV_THREAD 128 
 int /*<<< orphan*/  __aio_wake () ; 
 int /*<<< orphan*/  a_store (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_signal (struct sigevent*) ; 
 scalar_t__ pread (int,void*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ pwrite (int,void*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,void*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,void*,size_t) ; 

__attribute__((used)) static void *io_thread(void *p)
{
	struct aiocb *cb = p;
	int fd = cb->aio_fildes;
	void *buf = (void *)cb->aio_buf;
	size_t len = cb->aio_nbytes;
	off_t off = cb->aio_offset;
	int op = cb->aio_lio_opcode;
	struct sigevent sev = cb->aio_sigevent;
	ssize_t ret;

	if (op == LIO_WRITE) {
		if (  (fcntl(fd, F_GETFL) & O_APPEND)
		    ||((ret = pwrite(fd, buf, len, off))<0 && errno==ESPIPE) )
			ret = write(fd, buf, len);
	} else if (op == LIO_READ) {
		if ( (ret = pread(fd, buf, len, off))<0 && errno==ESPIPE )
			ret = read(fd, buf, len);
	} else {
		ret = 0;
	}
	cb->__ret = ret;

	if (ret < 0) a_store(&cb->__err, errno);
	else a_store(&cb->__err, 0);

	__aio_wake();

	switch (sev.sigev_notify) {
	case SIGEV_SIGNAL:
		notify_signal(&sev);
		break;
	case SIGEV_THREAD:
		sev.sigev_notify_function(sev.sigev_value);
		break;
	}

	return 0;
}