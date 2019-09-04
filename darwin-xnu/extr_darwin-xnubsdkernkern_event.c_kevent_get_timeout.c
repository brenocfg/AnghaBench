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
typedef  scalar_t__ user_addr_t ;
typedef  int /*<<< orphan*/  ts ;
struct user64_timespec {int tv_sec; } ;
struct user32_timespec {int tv_sec; } ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct timespec {int tv_sec; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 unsigned int KEVENT_FLAG_IMMEDIATE ; 
 unsigned int KEVENT_FLAG_KERNEL ; 
 int /*<<< orphan*/  TIMESPEC_TO_TIMEVAL (struct timeval*,struct user64_timespec*) ; 
 scalar_t__ USER_ADDR_NULL ; 
 int copyin (scalar_t__,struct user64_timespec*,int) ; 
 int /*<<< orphan*/  getmicrouptime (struct timeval*) ; 
 scalar_t__ itimerfix (struct timeval*) ; 
 int /*<<< orphan*/  timevaladd (struct timeval*,struct timeval*) ; 

__attribute__((used)) static int
kevent_get_timeout(struct proc *p,
		   user_addr_t utimeout,
		   unsigned int flags,
		   struct timeval *atvp)
{
	struct timeval atv;
	int error = 0;

	if (flags & KEVENT_FLAG_IMMEDIATE) {
		getmicrouptime(&atv);
	} else if (utimeout != USER_ADDR_NULL) {
		struct timeval rtv;
		if (flags & KEVENT_FLAG_KERNEL) {
			struct timespec *tsp = (struct timespec *)utimeout;
			TIMESPEC_TO_TIMEVAL(&rtv, tsp);
		} else if (IS_64BIT_PROCESS(p)) {
			struct user64_timespec ts;
			error = copyin(utimeout, &ts, sizeof(ts));
			if ((ts.tv_sec & 0xFFFFFFFF00000000ull) != 0)
				error = EINVAL;
			else
				TIMESPEC_TO_TIMEVAL(&rtv, &ts);
		} else {
			struct user32_timespec ts;
			error = copyin(utimeout, &ts, sizeof(ts));
			TIMESPEC_TO_TIMEVAL(&rtv, &ts);
		}
		if (error)
			return (error);
		if (itimerfix(&rtv))
			return (EINVAL);
		getmicrouptime(&atv);
		timevaladd(&atv, &rtv);
	} else {
		/* wait forever value */
		atv.tv_sec = 0;
		atv.tv_usec = 0;
	}
	*atvp = atv;
	return 0;
}