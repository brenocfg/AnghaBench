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
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  const sigset_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  scalar_t__ __darwin_suseconds_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_SETMASK ; 
 int __pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int errno ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
_pselect_emulated(int count, fd_set * __restrict rfds, fd_set * __restrict wfds,
		fd_set * __restrict efds, const struct timespec * __restrict timo,
		const sigset_t * __restrict mask)
{
	sigset_t omask;
	struct timeval tvtimo, *tvp;
	int rv, sverrno;

	if (timo) {
		tvtimo.tv_sec = timo->tv_sec;
		tvtimo.tv_usec = (__darwin_suseconds_t)(timo->tv_nsec / 1000);
		tvp = &tvtimo;
	} else {
		tvp = 0;
	}

	if (mask != 0) {
		rv = __pthread_sigmask(SIG_SETMASK, mask, &omask);
		if (rv != 0)
			return rv;
	}

	rv = select(count, rfds, wfds, efds, tvp);
	if (mask != 0) {
		sverrno = errno;
		__pthread_sigmask(SIG_SETMASK, &omask, (sigset_t *)0);
		errno = sverrno;
	}

	return rv;
}