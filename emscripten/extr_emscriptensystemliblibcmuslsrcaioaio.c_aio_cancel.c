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
struct aiocb {int aio_fildes; } ;
struct aio_thread {scalar_t__ err; int /*<<< orphan*/  running; int /*<<< orphan*/  td; struct aiocb* cb; struct aio_thread* next; } ;
struct aio_queue {int /*<<< orphan*/  lock; struct aio_thread* head; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int AIO_ALLDONE ; 
 int AIO_CANCELED ; 
 scalar_t__ ECANCELED ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 struct aio_queue* __aio_get_queue (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ a_cas (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 

int aio_cancel(int fd, struct aiocb *cb)
{
	sigset_t allmask, origmask;
	int ret = AIO_ALLDONE;
	struct aio_thread *p;
	struct aio_queue *q;

	/* Unspecified behavior case. Report an error. */
	if (cb && fd != cb->aio_fildes) {
		errno = EINVAL;
		return -1;
	}

	sigfillset(&allmask);
	pthread_sigmask(SIG_BLOCK, &allmask, &origmask);

	if (!(q = __aio_get_queue(fd, 0))) {
		if (fcntl(fd, F_GETFD) < 0) ret = -1;
		goto done;
	}

	for (p = q->head; p; p = p->next) {
		if (cb && cb != p->cb) continue;
		/* Transition target from running to running-with-waiters */
		if (a_cas(&p->running, 1, -1)) {
			pthread_cancel(p->td);
			__wait(&p->running, 0, -1, 1);
			if (p->err == ECANCELED) ret = AIO_CANCELED;
		}
	}

	pthread_mutex_unlock(&q->lock);
done:
	pthread_sigmask(SIG_SETMASK, &origmask, 0);
	return ret;
}