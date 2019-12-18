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
struct timezone {int dummy; } ;
struct timespec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int do_settimeofday (struct timespec const*) ; 
 int security_settime (struct timespec const*,struct timezone const*) ; 
 struct timezone sys_tz ; 
 int /*<<< orphan*/  timespec_valid (struct timespec const*) ; 
 int /*<<< orphan*/  update_vsyscall_tz () ; 
 int /*<<< orphan*/  warp_clock () ; 

int do_sys_settimeofday(const struct timespec *tv, const struct timezone *tz)
{
	static int firsttime = 1;
	int error = 0;

	if (tv && !timespec_valid(tv))
		return -EINVAL;

	error = security_settime(tv, tz);
	if (error)
		return error;

	if (tz) {
		/* SMP safe, global irq locking makes it work. */
		sys_tz = *tz;
		update_vsyscall_tz();
		if (firsttime) {
			firsttime = 0;
			if (!tv)
				warp_clock();
		}
	}
	if (tv)
	{
		/* SMP safe, again the code in arch/foo/time.c should
		 * globally block out interrupts when it runs.
		 */
		return do_settimeofday(tv);
	}
	return 0;
}