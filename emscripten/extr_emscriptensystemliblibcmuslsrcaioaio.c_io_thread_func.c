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
struct aiocb {int aio_fildes; size_t aio_nbytes; int /*<<< orphan*/  aio_offset; scalar_t__ aio_buf; } ;
struct aio_thread {int op; int running; int ret; int /*<<< orphan*/  err; struct aio_thread* next; struct aio_thread* prev; struct aiocb* cb; int /*<<< orphan*/  td; struct aio_queue* q; } ;
struct aio_queue {int init; int seekable; int append; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  ref; struct aio_thread* head; } ;
struct aio_args {int op; int /*<<< orphan*/  sem; int /*<<< orphan*/  err; struct aiocb* cb; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ECANCELED ; 
 int /*<<< orphan*/  F_GETFL ; 
#define  LIO_READ 131 
#define  LIO_WRITE 130 
 int O_APPEND ; 
#define  O_DSYNC 129 
#define  O_SYNC 128 
 int /*<<< orphan*/  SEEK_CUR ; 
 struct aio_queue* __aio_get_queue (int,int) ; 
 int /*<<< orphan*/  __pthread_self () ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 int fdatasync (int) ; 
 int fsync (int) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pread (int,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,struct aio_thread*) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int pwrite (int,void*,size_t,int /*<<< orphan*/ ) ; 
 int read (int,void*,size_t) ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 
 int write (int,void*,size_t) ; 

__attribute__((used)) static void *io_thread_func(void *ctx)
{
	struct aio_thread at, *p;

	struct aio_args *args = ctx;
	struct aiocb *cb = args->cb;
	int fd = cb->aio_fildes;
	int op = args->op;
	void *buf = (void *)cb->aio_buf;
	size_t len = cb->aio_nbytes;
	off_t off = cb->aio_offset;

	struct aio_queue *q = __aio_get_queue(fd, 1);
	ssize_t ret;

	args->err = q ? 0 : EAGAIN;
	sem_post(&args->sem);
	if (!q) return 0;

	at.op = op;
	at.running = 1;
	at.ret = -1;
	at.err = ECANCELED;
	at.q = q;
	at.td = __pthread_self();
	at.cb = cb;
	at.prev = 0;
	if ((at.next = q->head)) at.next->prev = &at;
	q->head = &at;
	q->ref++;

	if (!q->init) {
		int seekable = lseek(fd, 0, SEEK_CUR) >= 0;
		q->seekable = seekable;
		q->append = !seekable || (fcntl(fd, F_GETFL) & O_APPEND);
		q->init = 1;
	}

	pthread_cleanup_push(cleanup, &at);

	/* Wait for sequenced operations. */
	if (op!=LIO_READ && (op!=LIO_WRITE || q->append)) {
		for (;;) {
			for (p=at.next; p && p->op!=LIO_WRITE; p=p->next);
			if (!p) break;
			pthread_cond_wait(&q->cond, &q->lock);
		}
	}

	pthread_mutex_unlock(&q->lock);

	switch (op) {
	case LIO_WRITE:
		ret = q->append ? write(fd, buf, len) : pwrite(fd, buf, len, off);
		break;
	case LIO_READ:
		ret = !q->seekable ? read(fd, buf, len) : pread(fd, buf, len, off);
		break;
	case O_SYNC:
		ret = fsync(fd);
		break;
	case O_DSYNC:
		ret = fdatasync(fd);
		break;
	}
	at.ret = ret;
	at.err = ret<0 ? errno : 0;
	
	pthread_cleanup_pop(1);

	return 0;
}