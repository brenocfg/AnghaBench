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

/* Variables and functions */

int av_gettime_relative_is_monotonic(void)
{
#if HAVE_CLOCK_GETTIME && defined(CLOCK_MONOTONIC)
#ifdef __APPLE__
    if (!clock_gettime)
        return 0;
#endif
    return 1;
#else
    return 0;
#endif
}