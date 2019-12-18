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
typedef  int /*<<< orphan*/  timeout ;
struct timespec {scalar_t__ tv_sec; long tv_nsec; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOSYS ; 
 int FD_SETSIZE ; 
 int __pselect (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec const*,int /*<<< orphan*/  const*) ; 
 int __pselect_nocancel (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec const*,int /*<<< orphan*/  const*) ; 
 int _pselect_emulated (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ errno ; 

int
pselect(int nfds, fd_set * __restrict readfds, fd_set * __restrict writefds,
	fd_set * __restrict exceptfds, const struct timespec * __restrict
#if defined(VARIANT_LEGACY) || defined(VARIANT_PRE1050)
	intimeout,
#else /* !VARIANT_LEGACY && !VARIANT_PRE1050 */
	timeout,
#endif /* VARIANT_LEGACY || VARIANT_PRE1050 */
	const sigset_t * __restrict sigmask)
{
	int ret;
#if defined(VARIANT_LEGACY) || defined(VARIANT_PRE1050)
	struct timespec tb;
	const struct timespec *timeout;

	/*
	 * Legacy select behavior is minimum 10 msec when tv_usec is non-zero
	 */
	if (intimeout && intimeout->tv_sec == 0 && intimeout->tv_nsec > 0 && intimeout->tv_nsec < 10000000L) {
		tb.tv_sec = 0;
		tb.tv_nsec = 10000000L;
		timeout = &tb;
	} else {
		timeout = intimeout;
	}
#elif defined(VARIANT_DARWIN_EXTSN)
#else
	/* 1050 variant */
	if (nfds > FD_SETSIZE) {
		errno = EINVAL;
		return -1;
	}
#endif

#if defined(VARIANT_CANCELABLE) || defined(VARIANT_PRE1050)
	ret = __pselect(nfds, readfds, writefds, exceptfds, timeout, sigmask);
#else /* !VARIANT_CANCELABLE && !VARIANT_PRE1050 */
	ret = __pselect_nocancel(nfds, readfds, writefds, exceptfds, timeout, sigmask);
#endif /* VARIANT_CANCELABLE || VARIANT_PRE1050 */

	if (ret == -1 && errno == ENOSYS) {
		ret = _pselect_emulated(nfds, readfds, writefds, exceptfds, timeout, sigmask);
	}

	return ret;
}