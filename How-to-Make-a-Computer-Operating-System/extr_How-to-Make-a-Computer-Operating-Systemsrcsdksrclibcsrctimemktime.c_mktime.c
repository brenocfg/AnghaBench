#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tm_year; int tm_hour; int tm_min; int tm_sec; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; } ;
typedef  TYPE_1__ tm_t ;
typedef  int time_t ;

/* Variables and functions */
 int SECONDS_PER_DAY ; 
 int SECONDS_PER_HOUR ; 
 int SECONDS_PER_MINUTE ; 
 int daysdiff (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

time_t mktime( tm_t* tm ) {
    if ( tm->tm_year > 2100 ) {
        return -1;
    }

    return daysdiff( tm->tm_year, tm->tm_mon, tm->tm_mday ) * SECONDS_PER_DAY +
           tm->tm_hour * SECONDS_PER_HOUR + tm->tm_min * SECONDS_PER_MINUTE + tm->tm_sec;
}