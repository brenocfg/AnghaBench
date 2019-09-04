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
struct _throttle_io_info_t {scalar_t__ throttle_io_count; scalar_t__ throttle_io_count_begin; int /*<<< orphan*/ * throttle_window_start_timestamp; scalar_t__* throttle_inflight_count; } ;

/* Variables and functions */
 int THROTTLE_DISENGAGED ; 
 int THROTTLE_ENGAGED ; 
 int THROTTLE_LEVEL_START ; 
 int THROTTLE_LEVEL_THROTTLED ; 
 int THROTTLE_NOW ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 int throttle_get_thread_throttle_level (int /*<<< orphan*/ *) ; 
 scalar_t__* throttle_windows_msecs ; 
 int /*<<< orphan*/  timevalsub (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
throttle_io_will_be_throttled_internal(void * throttle_info, int * mylevel, int * throttling_level)
{
    	struct _throttle_io_info_t *info = throttle_info;
	struct timeval elapsed;
	struct timeval now;
	uint64_t elapsed_msecs;
	int	thread_throttle_level;
	int	throttle_level;

	if ((thread_throttle_level = throttle_get_thread_throttle_level(NULL)) < THROTTLE_LEVEL_THROTTLED)
		return (THROTTLE_DISENGAGED);

	microuptime(&now);

	for (throttle_level = THROTTLE_LEVEL_START; throttle_level < thread_throttle_level; throttle_level++) {
		if (info->throttle_inflight_count[throttle_level]) {
			break;
		}
		elapsed = now;
		timevalsub(&elapsed, &info->throttle_window_start_timestamp[throttle_level]);
		elapsed_msecs = (uint64_t)elapsed.tv_sec * (uint64_t)1000 + (elapsed.tv_usec / 1000);

		if (elapsed_msecs < (uint64_t)throttle_windows_msecs[thread_throttle_level])
			break;
	}
	if (throttle_level >= thread_throttle_level) {
		/*
		 * we're beyond all of the throttle windows
		 * that affect the throttle level of this thread,
		 * so go ahead and treat as normal I/O
		 */
		return (THROTTLE_DISENGAGED);
	}
	if (mylevel)
		*mylevel = thread_throttle_level;
	if (throttling_level)
		*throttling_level = throttle_level;

	if (info->throttle_io_count != info->throttle_io_count_begin) {
		/*
		 * we've already issued at least one throttleable I/O
		 * in the current I/O window, so avoid issuing another one
		 */
		return (THROTTLE_NOW);
	}
	/*
	 * we're in the throttle window, so
	 * cut the I/O size back
	 */
	return (THROTTLE_ENGAGED);
}