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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  AVIOInterruptCB ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXIT ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  FFMIN (scalar_t__,int) ; 
 int POLLING_TIME ; 
 scalar_t__ av_gettime_relative () ; 
 int /*<<< orphan*/  av_usleep (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_check_interrupt (int /*<<< orphan*/ *) ; 

int ff_network_sleep_interruptible(int64_t timeout, AVIOInterruptCB *int_cb)
{
    int64_t wait_start = av_gettime_relative();

    while (1) {
        int64_t time_left;

        if (ff_check_interrupt(int_cb))
            return AVERROR_EXIT;

        time_left = timeout - (av_gettime_relative() - wait_start);
        if (time_left <= 0)
            return AVERROR(ETIMEDOUT);

        av_usleep(FFMIN(time_left, POLLING_TIME * 1000));
    }
}