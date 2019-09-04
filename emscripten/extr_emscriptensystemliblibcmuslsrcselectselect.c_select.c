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
typedef  scalar_t__ const time_t ;
typedef  int syscall_arg_t ;
struct timeval {scalar_t__ tv_sec; int tv_usec; } ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SYS_pselect6 ; 
 int _NSIG ; 
 int __syscall_ret (int /*<<< orphan*/ ) ; 
 int syscall_cp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*,int*) ; 

int select(int n, fd_set *restrict rfds, fd_set *restrict wfds, fd_set *restrict efds, struct timeval *restrict tv)
{
#ifdef SYS_select
	return syscall_cp(SYS_select, n, rfds, wfds, efds, tv);
#else
	syscall_arg_t data[2] = { 0, _NSIG/8 };
	struct timespec ts;
	if (tv) {
		if (tv->tv_sec < 0 || tv->tv_usec < 0)
			return __syscall_ret(-EINVAL);
		time_t extra_secs = tv->tv_usec / 1000000;
		ts.tv_nsec = tv->tv_usec % 1000000 * 1000;
		const time_t max_time = (1ULL<<8*sizeof(time_t)-1)-1;
		ts.tv_sec = extra_secs > max_time - tv->tv_sec ?
			max_time : tv->tv_sec + extra_secs;
	}
	return syscall_cp(SYS_pselect6, n, rfds, wfds, efds, tv ? &ts : 0, data);
#endif
}