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
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int FD_SETSIZE ; 
 int __select_nocancel (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  errno ; 

int
select(int nfds, fd_set * __restrict readfds, fd_set * __restrict writefds,
	fd_set * __restrict exceptfds, struct timeval * __restrict
#if defined(VARIANT_LEGACY) || defined(VARIANT_PRE1050)
	intimeout
#else /* !VARIANT_LEGACY && !VARIANT_PRE1050 */
	timeout
#endif /* VARIANT_LEGACY || VARIANT_PRE1050 */
	)
{
#if defined(VARIANT_LEGACY) || defined(VARIANT_PRE1050)
	struct timeval tb, *timeout;

	/*
	 * Legacy select behavior is minimum 10 msec when tv_usec is non-zero
	 */
	if (intimeout && intimeout->tv_sec == 0 && intimeout->tv_usec > 0 && intimeout->tv_usec < 10000) {
		tb.tv_sec = 0;
		tb.tv_usec = 10000;
		timeout = &tb;
	} else {
		timeout = intimeout;
	}
#else /* !VARIANT_LEGACY && !VARIANT_PRE1050 */
	if (nfds > FD_SETSIZE) {
		errno = EINVAL;
		return -1;
	}
#endif

#if defined(VARIANT_CANCELABLE) || defined(VARIANT_PRE1050)
	return __select(nfds, readfds, writefds, exceptfds, timeout);
#else /* !VARIANT_CANCELABLE && !VARIANT_PRE1050 */
	return __select_nocancel(nfds, readfds, writefds, exceptfds, timeout);
#endif /* VARIANT_CANCELABLE || VARIANT_PRE1050 */
}