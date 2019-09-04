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
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
struct aiocb {int /*<<< orphan*/  __err; } ;
struct TYPE_2__ {int tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int EAGAIN ; 
#define  ECANCELED 130 
 scalar_t__ EINPROGRESS ; 
#define  EINTR 129 
 int EINVAL ; 
#define  ETIMEDOUT 128 
 int __aio_fut ; 
 TYPE_1__* __pthread_self () ; 
 int __timedwait_cp (int volatile*,int,int /*<<< orphan*/ ,struct timespec*,int) ; 
 int a_cas (int volatile*,scalar_t__,int) ; 
 scalar_t__ aio_error (struct aiocb const* const) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int errno ; 
 int /*<<< orphan*/  pthread_testcancel () ; 

int aio_suspend(const struct aiocb *const cbs[], int cnt, const struct timespec *ts)
{
	int i, tid = 0, ret, expect = 0;
	struct timespec at;
	volatile int dummy_fut, *pfut;
	int nzcnt = 0;
	const struct aiocb *cb = 0;

	pthread_testcancel();

	if (cnt<0) {
		errno = EINVAL;
		return -1;
	}

	for (i=0; i<cnt; i++) if (cbs[i]) {
		if (aio_error(cbs[i]) != EINPROGRESS) return 0;
		nzcnt++;
		cb = cbs[i];
	}

	if (ts) {
		clock_gettime(CLOCK_MONOTONIC, &at);
		at.tv_sec += ts->tv_sec;
		if ((at.tv_nsec += ts->tv_nsec) >= 1000000000) {
			at.tv_nsec -= 1000000000;
			at.tv_sec++;
		}
	}

	for (;;) {
		for (i=0; i<cnt; i++)
			if (cbs[i] && aio_error(cbs[i]) != EINPROGRESS)
				return 0;

		switch (nzcnt) {
		case 0:
			pfut = &dummy_fut;
			break;
		case 1:
			pfut = (void *)&cb->__err;
			expect = EINPROGRESS | 0x80000000;
			a_cas(pfut, EINPROGRESS, expect);
			break;
		default:
			pfut = &__aio_fut;
			if (!tid) tid = __pthread_self()->tid;
			expect = a_cas(pfut, 0, tid);
			if (!expect) expect = tid;
			/* Need to recheck the predicate before waiting. */
			for (i=0; i<cnt; i++)
				if (cbs[i] && aio_error(cbs[i]) != EINPROGRESS)
					return 0;
			break;
		}

		ret = __timedwait_cp(pfut, expect, CLOCK_MONOTONIC, ts?&at:0, 1);

		switch (ret) {
		case ETIMEDOUT:
			ret = EAGAIN;
		case ECANCELED:
		case EINTR:
			errno = ret;
			return -1;
		}
	}
}