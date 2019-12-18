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
struct timeval {long tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {long tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int clockid_t ;

/* Variables and functions */
#define  CLOCK_REALTIME 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  settimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

int clock_settime (clockid_t clock_id, const struct timespec *tp)
{
#if defined( WITH_FRC ) || defined( WITH_RTC )
    if (tp == NULL) {
        errno = EINVAL;
        return -1;
    }
    struct timeval tv;
    switch (clock_id) {
        case CLOCK_REALTIME:
            tv.tv_sec = tp->tv_sec;
            tv.tv_usec = tp->tv_nsec / 1000L;
            settimeofday(&tv, NULL);
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