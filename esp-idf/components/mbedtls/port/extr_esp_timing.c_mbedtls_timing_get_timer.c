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
struct timeval {unsigned long tv_sec; int tv_usec; } ;
struct mbedtls_timing_hr_time {int dummy; } ;
struct _hr_time {struct timeval start; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

unsigned long mbedtls_timing_get_timer( struct mbedtls_timing_hr_time *val, int reset )
{
    struct _hr_time *t = (struct _hr_time *) val;

    if( reset )
    {
        gettimeofday( &t->start, NULL );
        return( 0 );
    }
    else
    {
        unsigned long delta;
        struct timeval now;
        gettimeofday( &now, NULL );
        delta = ( now.tv_sec  - t->start.tv_sec  ) * 1000ul
              + ( now.tv_usec - t->start.tv_usec ) / 1000;
        return( delta );
    }
}