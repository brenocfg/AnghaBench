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
struct timeval {long tv_sec; long tv_usec; } ;
typedef  long int64_t ;

/* Variables and functions */
 long INT_MAX ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release (int /*<<< orphan*/ *) ; 
 scalar_t__ adjtime_start ; 
 long adjtime_total_correction ; 
 int /*<<< orphan*/  adjust_boot_time () ; 
 scalar_t__ get_time_since_boot () ; 
 long llabs (long) ; 
 int /*<<< orphan*/  s_adjust_time_lock ; 

int adjtime(const struct timeval *delta, struct timeval *outdelta)
{
#if defined( WITH_FRC ) || defined( WITH_RTC )
    if(delta != NULL){
        int64_t sec  = delta->tv_sec;
        int64_t usec = delta->tv_usec;
        if(llabs(sec) > ((INT_MAX / 1000000L) - 1L)) {
            return -1;
        }
        /*
        * If adjusting the system clock by adjtime () is already done during the second call adjtime (),
        * and the delta of the second call is not NULL, the earlier tuning is stopped,
        * but the already completed part of the adjustment is not canceled.
        */
        _lock_acquire(&s_adjust_time_lock);
        // If correction is already in progress (adjtime_start != 0), then apply accumulated corrections.
        adjust_boot_time();
        adjtime_start = get_time_since_boot();
        adjtime_total_correction = sec * 1000000L + usec;
        _lock_release(&s_adjust_time_lock);
    }
    if(outdelta != NULL){
        _lock_acquire(&s_adjust_time_lock);
        adjust_boot_time();
        if (adjtime_start != 0) {
            outdelta->tv_sec    = adjtime_total_correction / 1000000L;
            outdelta->tv_usec   = adjtime_total_correction % 1000000L;
        } else {
            outdelta->tv_sec    = 0;
            outdelta->tv_usec   = 0;
        }
        _lock_release(&s_adjust_time_lock);
    }
  return 0;
#else
  return -1;
#endif

}