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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int MAX_TIMEBASE_TRIES ; 
 int /*<<< orphan*/  OSCompareAndSwap64 (scalar_t__,scalar_t__,scalar_t__ volatile*) ; 
 int /*<<< orphan*/  OSSynchronizeIO () ; 
 scalar_t__ __improbable (int) ; 
 int absolute_time_validation ; 
 scalar_t__ ml_get_timebase () ; 
 int /*<<< orphan*/  panic (char*,scalar_t__,scalar_t__) ; 

uint64_t
mach_absolute_time(void)
{
#if DEVELOPMENT || DEBUG
	if (__improbable(absolute_time_validation == 1)) {
		static volatile uint64_t s_last_absolute_time = 0;
		uint64_t                 new_absolute_time, old_absolute_time;
		int                      attempts = 0;

		/* ARM 64: We need a dsb here to ensure that the load of s_last_absolute_time
		 * completes before the timebase read. Were the load to complete after the
		 * timebase read, there would be a window for another CPU to update
		 * s_last_absolute_time and leave us in an inconsistent state. Consider the
		 * following interleaving:
		 *
		 *   Let s_last_absolute_time = t0
		 *   CPU0: Read timebase at t1
		 *   CPU1: Read timebase at t2
		 *   CPU1: Update s_last_absolute_time to t2
		 *   CPU0: Load completes
		 *   CPU0: Update s_last_absolute_time to t1
		 *
		 * This would cause the assertion to fail even though time did not go
		 * backwards. Thus, we use a dsb to guarantee completion of the load before
		 * the timebase read.
		 */
		do {
			attempts++;
			old_absolute_time = s_last_absolute_time;

#if __arm64__
			__asm__ volatile("dsb ld" ::: "memory");
#else
			OSSynchronizeIO(); // See osfmk/arm64/rtclock.c
#endif

			new_absolute_time = ml_get_timebase();
		} while (attempts < MAX_TIMEBASE_TRIES && !OSCompareAndSwap64(old_absolute_time, new_absolute_time, &s_last_absolute_time));

		if (attempts < MAX_TIMEBASE_TRIES && old_absolute_time > new_absolute_time) {
			panic("mach_absolute_time returning non-monotonically increasing value 0x%llx (old value 0x%llx\n)\n",
			    new_absolute_time, old_absolute_time);
		}
		return new_absolute_time;
	} else {
		return ml_get_timebase();
	}
#else
	return ml_get_timebase();
#endif
}