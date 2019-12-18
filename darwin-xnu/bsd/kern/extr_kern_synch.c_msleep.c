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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_int64_t ;
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 int _sleep (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int (*) (int),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nanoseconds_to_absolutetime (scalar_t__,int /*<<< orphan*/ *) ; 

int
msleep(
	void		*chan,
	lck_mtx_t	*mtx,
	int		pri,
	const char	*wmsg,
	struct timespec		*ts)
{
	u_int64_t	abstime = 0;

	if (ts && (ts->tv_sec || ts->tv_nsec)) {
		nanoseconds_to_absolutetime((uint64_t)ts->tv_sec * NSEC_PER_SEC + ts->tv_nsec,  &abstime );
		clock_absolutetime_interval_to_deadline( abstime, &abstime );
	}

	return _sleep((caddr_t)chan, pri, wmsg, abstime, (int (*)(int))0, mtx);
}