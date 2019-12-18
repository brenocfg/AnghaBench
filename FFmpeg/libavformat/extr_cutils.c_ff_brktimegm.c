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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int tm_year; int tm_mon; } ;

/* Variables and functions */
 struct tm* gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 

struct tm *ff_brktimegm(time_t secs, struct tm *tm)
{
    tm = gmtime_r(&secs, tm);

    tm->tm_year += 1900; /* unlike gmtime_r we store complete year here */
    tm->tm_mon  += 1;    /* unlike gmtime_r tm_mon is from 1 to 12 */

    return tm;
}