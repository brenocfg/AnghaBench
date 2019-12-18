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
typedef  long long uint64_t ;
struct timeval {long long tv_sec; long tv_usec; } ;
struct timespec {long long tv_sec; long tv_nsec; } ;
typedef  int clockid_t ;

/* Variables and functions */
#define  CLOCK_MONOTONIC 129 
#define  CLOCK_REALTIME 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  _gettimeofday_r (int /*<<< orphan*/ *,struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  esp_timer_get_time () ; 
 long long get_rtc_time_us () ; 

int clock_gettime (clockid_t clock_id, struct timespec *tp)
{
#if defined( WITH_FRC ) || defined( WITH_RTC )
    if (tp == NULL) {
        errno = EINVAL;
        return -1;
    }
    struct timeval tv;
    uint64_t monotonic_time_us = 0;
    switch (clock_id) {
        case CLOCK_REALTIME:
            _gettimeofday_r(NULL, &tv, NULL);
            tp->tv_sec = tv.tv_sec;
            tp->tv_nsec = tv.tv_usec * 1000L;
            break;
        case CLOCK_MONOTONIC:
#if defined( WITH_FRC )
            monotonic_time_us = (uint64_t) esp_timer_get_time();
#elif defined( WITH_RTC )
            monotonic_time_us = get_rtc_time_us();
#endif // WITH_FRC
            tp->tv_sec = monotonic_time_us / 1000000LL;
            tp->tv_nsec = (monotonic_time_us % 1000000LL) * 1000L;
            break;
        default:
            errno = EINVAL;
            return -1;
    }
    return 0;
#else
    errno = ENOSYS;
    return -1;
#endif
}