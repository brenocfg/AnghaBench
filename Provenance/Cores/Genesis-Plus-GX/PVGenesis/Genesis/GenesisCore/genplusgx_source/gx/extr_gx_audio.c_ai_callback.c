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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 size_t LOGSIZE ; 
 scalar_t__ audio_sync ; 
 int /*<<< orphan*/ * delta_time ; 
 int /*<<< orphan*/  diff_nsec (scalar_t__,scalar_t__) ; 
 size_t frame_cnt ; 
 scalar_t__ gettime () ; 
 scalar_t__ prevtime ; 

__attribute__((used)) static void ai_callback(void)
{
#ifdef LOG_TIMING
  u64 current = gettime();
  if (prevtime)
  {
    delta_time[frame_cnt] = diff_nsec(prevtime, current);
    frame_cnt = (frame_cnt + 1) % LOGSIZE;
  }
  prevtime = current;
#endif

  audio_sync = 0;
}