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
struct sigevent {scalar_t__ sigev_notify; int /*<<< orphan*/ * sigev_notify_attributes; } ;
struct lio_state {int cnt; int /*<<< orphan*/  cbs; struct sigevent* sev; } ;
struct aiocb {int aio_lio_opcode; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
#define  LIO_READ 129 
 int LIO_WAIT ; 
#define  LIO_WRITE 128 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 scalar_t__ SIGEV_NONE ; 
 scalar_t__ SIGEV_THREAD ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int aio_read (struct aiocb* const) ; 
 int aio_write (struct aiocb* const) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct lio_state*) ; 
 int lio_wait (struct lio_state*) ; 
 struct lio_state* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_setguardsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_setstacksize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct lio_state*) ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_thread ; 

int lio_listio(int mode, struct aiocb *restrict const *restrict cbs, int cnt, struct sigevent *restrict sev)
{
	int i, ret;
	struct lio_state *st=0;

	if (cnt < 0) {
		errno = EINVAL;
		return -1;
	}

	if (mode == LIO_WAIT || (sev && sev->sigev_notify != SIGEV_NONE)) {
		if (!(st = malloc(sizeof *st + cnt*sizeof *cbs))) {
			errno = EAGAIN;
			return -1;
		}
		st->cnt = cnt;
		st->sev = sev;
		memcpy(st->cbs, (void*) cbs, cnt*sizeof *cbs);
	}

	for (i=0; i<cnt; i++) {
		if (!cbs[i]) continue;
		switch (cbs[i]->aio_lio_opcode) {
		case LIO_READ:
			ret = aio_read(cbs[i]);
			break;
		case LIO_WRITE:
			ret = aio_write(cbs[i]);
			break;
		default:
			continue;
		}
		if (ret) {
			free(st);
			errno = EAGAIN;
			return -1;
		}
	}

	if (mode == LIO_WAIT) {
		ret = lio_wait(st);
		free(st);
		return ret;
	}

	if (st) {
		pthread_attr_t a;
		sigset_t set;
		pthread_t td;

		if (sev->sigev_notify == SIGEV_THREAD) {
			if (sev->sigev_notify_attributes)
				a = *sev->sigev_notify_attributes;
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
		if (pthread_create(&td, &a, wait_thread, st)) {
			free(st);
			errno = EAGAIN;
			return -1;
		}
		pthread_sigmask(SIG_SETMASK, &set, 0);
	}

	return 0;
}