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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct _throttle_io_info_t {int /*<<< orphan*/ * throttle_window_start_timestamp; scalar_t__* throttle_inflight_count; } ;

/* Variables and functions */
#define  IOPOL_STANDARD 130 
#define  IOPOL_THROTTLE 129 
#define  IOPOL_UTILITY 128 
 int THROTTLE_DISENGAGED ; 
 int THROTTLE_ENGAGED ; 
 int THROTTLE_LEVEL_START ; 
 int THROTTLE_LEVEL_TIER0 ; 
 int THROTTLE_LEVEL_TIER1 ; 
 int THROTTLE_LEVEL_TIER2 ; 
 int THROTTLE_LEVEL_TIER3 ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 scalar_t__* throttle_windows_msecs ; 
 int /*<<< orphan*/  timevalsub (struct timeval*,int /*<<< orphan*/ *) ; 

int throttle_info_io_will_be_throttled(void * throttle_info, int policy)
{
    	struct _throttle_io_info_t *info = throttle_info;
	struct timeval elapsed;
	uint64_t elapsed_msecs;
	int	throttle_level;
	int	thread_throttle_level;

        switch (policy) {

        case IOPOL_THROTTLE:
                thread_throttle_level = THROTTLE_LEVEL_TIER3;
                break;
        case IOPOL_UTILITY:
                thread_throttle_level = THROTTLE_LEVEL_TIER2;
                break;
        case IOPOL_STANDARD:
                thread_throttle_level = THROTTLE_LEVEL_TIER1;
                break;
        default:
                thread_throttle_level = THROTTLE_LEVEL_TIER0;
		break;
	}
	for (throttle_level = THROTTLE_LEVEL_START; throttle_level < thread_throttle_level; throttle_level++) {
		if (info->throttle_inflight_count[throttle_level]) {
			break;
		}

		microuptime(&elapsed);
		timevalsub(&elapsed, &info->throttle_window_start_timestamp[throttle_level]);
		elapsed_msecs = (uint64_t)elapsed.tv_sec * (uint64_t)1000 + (elapsed.tv_usec / 1000);

		if (elapsed_msecs < (uint64_t)throttle_windows_msecs[thread_throttle_level])
			break;
	}
	if (throttle_level >= thread_throttle_level) {
		/*
		 * we're beyond all of the throttle windows
		 * so go ahead and treat as normal I/O
		 */
		return (THROTTLE_DISENGAGED);
	}
	/*
	 * we're in the throttle window
	 */
	return (THROTTLE_ENGAGED);
}