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
typedef  int /*<<< orphan*/  tv64 ;
typedef  int /*<<< orphan*/  tv32 ;
struct user64_timeval {scalar_t__ tv_sec; int tv_usec; } ;
struct user32_timeval {scalar_t__ tv_sec; int tv_usec; } ;
struct timeval {scalar_t__ tv_sec; int tv_usec; } ;
struct sockopt {scalar_t__ sopt_p; int sopt_valsize; int /*<<< orphan*/  sopt_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_DOWN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EDOM ; 
 int EINVAL ; 
 scalar_t__ LONG_MAX ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,struct user64_timeval*,int) ; 
 int /*<<< orphan*/  caddr_t ; 
 int copyin (int /*<<< orphan*/ ,struct user64_timeval*,int) ; 
 scalar_t__ kernproc ; 
 scalar_t__ proc_is64bit (scalar_t__) ; 

__attribute__((used)) static int
sooptcopyin_timeval(struct sockopt *sopt, struct timeval *tv_p)
{
	int			error;

	if (proc_is64bit(sopt->sopt_p)) {
		struct user64_timeval	tv64;

		if (sopt->sopt_valsize < sizeof (tv64))
			return (EINVAL);

		sopt->sopt_valsize = sizeof (tv64);
		if (sopt->sopt_p != kernproc) {
			error = copyin(sopt->sopt_val, &tv64, sizeof (tv64));
			if (error != 0)
				return (error);
		} else {
			bcopy(CAST_DOWN(caddr_t, sopt->sopt_val), &tv64,
			    sizeof (tv64));
		}
		if (tv64.tv_sec < 0 || tv64.tv_sec > LONG_MAX ||
		    tv64.tv_usec < 0 || tv64.tv_usec >= 1000000)
			return (EDOM);

		tv_p->tv_sec = tv64.tv_sec;
		tv_p->tv_usec = tv64.tv_usec;
	} else {
		struct user32_timeval	tv32;

		if (sopt->sopt_valsize < sizeof (tv32))
			return (EINVAL);

		sopt->sopt_valsize = sizeof (tv32);
		if (sopt->sopt_p != kernproc) {
			error = copyin(sopt->sopt_val, &tv32, sizeof (tv32));
			if (error != 0) {
				return (error);
			}
		} else {
			bcopy(CAST_DOWN(caddr_t, sopt->sopt_val), &tv32,
			    sizeof (tv32));
		}
#ifndef __LP64__
		/*
		 * K64todo "comparison is always false due to
		 * limited range of data type"
		 */
		if (tv32.tv_sec < 0 || tv32.tv_sec > LONG_MAX ||
		    tv32.tv_usec < 0 || tv32.tv_usec >= 1000000)
			return (EDOM);
#endif
		tv_p->tv_sec = tv32.tv_sec;
		tv_p->tv_usec = tv32.tv_usec;
	}
	return (0);
}