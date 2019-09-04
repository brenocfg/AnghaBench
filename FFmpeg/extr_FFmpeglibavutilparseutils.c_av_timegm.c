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
typedef  long long time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; scalar_t__ tm_sec; } ;

/* Variables and functions */

time_t av_timegm(struct tm *tm)
{
    time_t t;

    int y = tm->tm_year + 1900, m = tm->tm_mon + 1, d = tm->tm_mday;

    if (m < 3) {
        m += 12;
        y--;
    }

    t = 86400LL *
        (d + (153 * m - 457) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 719469);

    t += 3600 * tm->tm_hour + 60 * tm->tm_min + tm->tm_sec;

    return t;
}