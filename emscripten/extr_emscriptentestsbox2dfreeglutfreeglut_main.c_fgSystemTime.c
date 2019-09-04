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

unsigned long fgSystemTime(void) {
#if TARGET_HOST_SOLARIS || HAVE_GETTIMEOFDAY
    struct timeval now;
    gettimeofday( &now, NULL );
    return now.tv_usec/1000 + now.tv_sec*1000;
#elif TARGET_HOST_MS_WINDOWS
#    if defined(_WIN32_WCE)
    return GetTickCount();
#    else
    return timeGetTime();
#    endif
#endif
}