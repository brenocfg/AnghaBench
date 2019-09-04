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
struct TYPE_2__ {scalar_t__ sigev_notify; int /*<<< orphan*/ * sigev_notify_attributes; } ;
struct aiocb {int /*<<< orphan*/  __err; TYPE_1__ aio_sigevent; } ;
struct aio_args {int op; scalar_t__ err; int /*<<< orphan*/  sem; struct aiocb* cb; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 int /*<<< orphan*/  PTHREAD_STACK_MIN ; 
 scalar_t__ SIGEV_THREAD ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  io_thread_func ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_setguardsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_setstacksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct aio_args*) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int submit(struct aiocb *cb, int op)
{
	int ret = 0;
	pthread_attr_t a;
	sigset_t allmask, origmask;
	pthread_t td;
	struct aio_args args = { .cb = cb, .op = op };
	sem_init(&args.sem, 0, 0);

	if (cb->aio_sigevent.sigev_notify == SIGEV_THREAD) {
		if (cb->aio_sigevent.sigev_notify_attributes)
			a = *cb->aio_sigevent.sigev_notify_attributes;
		else
			pthread_attr_init(&a);
	} else {
		pthread_attr_init(&a);
		pthread_attr_setstacksize(&a, PTHREAD_STACK_MIN);
		pthread_attr_setguardsize(&a, 0);
	}
	pthread_attr_setdetachstate(&a, PTHREAD_CREATE_DETACHED);
	sigfillset(&allmask);
	pthread_sigmask(SIG_BLOCK, &allmask, &origmask);
	cb->__err = EINPROGRESS;
	if (pthread_create(&td, &a, io_thread_func, &args)) {
		errno = EAGAIN;
		ret = -1;
	}
	pthread_sigmask(SIG_SETMASK, &origmask, 0);

	if (!ret) {
		while (sem_wait(&args.sem));
		if (args.err) {
			errno = args.err;
			ret = -1;
		}
	}

	return ret;
}