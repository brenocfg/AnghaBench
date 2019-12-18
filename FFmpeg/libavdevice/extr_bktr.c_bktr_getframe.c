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
 int /*<<< orphan*/  AV_LOG_INFO ; 
 scalar_t__ av_gettime () ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ last_frame_time ; 
 scalar_t__ nsignals ; 
 int /*<<< orphan*/  usleep (scalar_t__) ; 

__attribute__((used)) static void bktr_getframe(uint64_t per_frame)
{
    uint64_t curtime;

    curtime = av_gettime();
    if (!last_frame_time
        || ((last_frame_time + per_frame) > curtime)) {
        if (!usleep(last_frame_time + per_frame + per_frame / 8 - curtime)) {
            if (!nsignals)
                av_log(NULL, AV_LOG_INFO,
                       "SLEPT NO signals - %d microseconds late\n",
                       (int)(av_gettime() - last_frame_time - per_frame));
        }
    }
    nsignals = 0;
    last_frame_time = curtime;
}