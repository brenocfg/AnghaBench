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
struct TYPE_3__ {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_year; int tm_yday; int tm_mon; int tm_mday; int tm_isdst; } ;
typedef  TYPE_1__ tm_t ;
typedef  int time_t ;

/* Variables and functions */
 void* EPOCH ; 
 int HOURS_PER_DAY ; 
 int MINUTES_PER_HOUR ; 
 int SECONDS_PER_MINUTE ; 
 int* monthdays ; 
 int* monthdays2 ; 
 int* sumofdays ; 

int _gmtime( time_t timeval, tm_t* ret ) {
    int i;

    ret->tm_sec = timeval % SECONDS_PER_MINUTE;
    timeval /= SECONDS_PER_MINUTE;
    ret->tm_min = timeval % MINUTES_PER_HOUR;
    timeval /= MINUTES_PER_HOUR;
    ret->tm_hour = timeval % HOURS_PER_DAY;
    timeval /= HOURS_PER_DAY;

    /* 1970(Epoch) is a leap year, and every 4th year too.
       2000 is also a leap year, because its divisible by 400.
       timeval now holds the difference of whole days.
       1 Jan 1970 was a Thursday. */

    ret->tm_wday = (4 + timeval) % 7;

    /* TODO: return NULL when year does not fit. */
    ret->tm_year = EPOCH;

    for ( i = 0; i < 60; i++ ) {
        if ( sumofdays[ i ] > timeval ) {
            ret->tm_year = EPOCH + i - 1;
            timeval -= sumofdays[ i - 1 ];

            break;
        }
    }

    ret->tm_yday = ( int )timeval;

    if ( ret->tm_year % 4 == 0 ) {
        for ( ret->tm_mon = 0; ret->tm_mon < 12; ret->tm_mon++ ) {
            if ( monthdays2[ ret->tm_mon ] > timeval ) {
                timeval -= monthdays2[ --ret->tm_mon ];
                break;
            }
        }
    } else {
        for ( ret->tm_mon = 0; ret->tm_mon < 12; ret->tm_mon++ ) {
            if ( monthdays[ ret->tm_mon ] > timeval ) {
                timeval -= monthdays[ --ret->tm_mon ];
                break;
            }
        }
    }

    ret->tm_mday = ( int )timeval + 1;
    ret->tm_isdst = -1;

    return 0;
}