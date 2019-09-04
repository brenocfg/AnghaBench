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
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOSYS ; 

int av_usleep(unsigned usec)
{
#if HAVE_NANOSLEEP
    struct timespec ts = { usec / 1000000, usec % 1000000 * 1000 };
    while (nanosleep(&ts, &ts) < 0 && errno == EINTR);
    return 0;
#elif HAVE_USLEEP
    return usleep(usec);
#elif HAVE_SLEEP
    Sleep(usec / 1000);
    return 0;
#else
    return AVERROR(ENOSYS);
#endif
}