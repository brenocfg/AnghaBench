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
struct tm {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct TYPE_3__ {int /*<<< orphan*/  sec; int /*<<< orphan*/  min; int /*<<< orphan*/  hour; int /*<<< orphan*/  day; scalar_t__ mon; scalar_t__ year; } ;
typedef  TYPE_1__ mbedtls_x509_time ;
typedef  int /*<<< orphan*/  mbedtls_time_t ;

/* Variables and functions */
 int MBEDTLS_ERR_THREADING_MUTEX_ERROR ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mbedtls_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_threading_gmtime_mutex ; 
 int /*<<< orphan*/  mbedtls_time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int x509_get_current_time( mbedtls_x509_time *now )
{
    struct tm *lt;
    mbedtls_time_t tt;
    int ret = 0;

#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_lock( &mbedtls_threading_gmtime_mutex ) != 0 )
        return( MBEDTLS_ERR_THREADING_MUTEX_ERROR );
#endif

    tt = mbedtls_time( NULL );
    lt = gmtime( &tt );

    if( lt == NULL )
        ret = -1;
    else
    {
        now->year = lt->tm_year + 1900;
        now->mon  = lt->tm_mon  + 1;
        now->day  = lt->tm_mday;
        now->hour = lt->tm_hour;
        now->min  = lt->tm_min;
        now->sec  = lt->tm_sec;
    }

#if defined(MBEDTLS_THREADING_C)
    if( mbedtls_mutex_unlock( &mbedtls_threading_gmtime_mutex ) != 0 )
        return( MBEDTLS_ERR_THREADING_MUTEX_ERROR );
#endif

    return( ret );
}