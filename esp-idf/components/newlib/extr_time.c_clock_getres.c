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
typedef  long uint32_t ;
struct timespec {long tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 long rtc_clk_slow_freq_get_hz () ; 

int clock_getres (clockid_t clock_id, struct timespec *res)
{
#if defined( WITH_FRC ) || defined( WITH_RTC )
    if (res == NULL) {
        errno = EINVAL;
        return -1;
    }
#if defined( WITH_FRC )
    res->tv_sec = 0;
    res->tv_nsec = 1000L;
#elif defined( WITH_RTC )
    res->tv_sec = 0;
    uint32_t rtc_freq = rtc_clk_slow_freq_get_hz();
    assert(rtc_freq != 0);
    res->tv_nsec = 1000000000L / rtc_freq;
#endif // WITH_FRC
    return 0;
#else
    errno = ENOSYS;
    return -1;
#endif
}