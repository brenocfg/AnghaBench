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
struct aiocb {int /*<<< orphan*/  __td; int /*<<< orphan*/  __err; TYPE_1__ aio_sigevent; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 scalar_t__ SIGEV_THREAD ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  io_thread ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_setguardsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_setstacksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct aiocb*) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int new_req(struct aiocb *cb)
{
	int ret = 0;
	pthread_attr_t a;
	sigset_t set;
	pthread_t td;

	if (cb->aio_sigevent.sigev_notify == SIGEV_THREAD) {
		if (cb->aio_sigevent.sigev_notify_attributes)
			a = *cb->aio_sigevent.sigev_notify_attributes;
		else
			pthread_attr_init(&a);
	} else {
		pthread_attr_init(&a);
		pthread_attr_setstacksize(&a, PAGE_SIZE);
		pthread_attr_setguardsize(&a, 0);
	}
	pthread_attr_setdetachstate(&a, PTHREAD_CREATE_DETACHED);
	sigfillset(&set);
	pthread_sigmask(SIG_BLOCK, &set, &set);
	cb->__err = EINPROGRESS;
	if (pthread_create(&td, &a, io_thread, cb)) {
		errno = EAGAIN;
		ret = -1;
	}
	pthread_sigmask(SIG_SETMASK, &set, 0);
	cb->__td = td;

	return ret;
}