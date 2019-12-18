#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int year; int mon; int day; int hour; int min; int sec; } ;
typedef  TYPE_1__ mbedtls_x509_time ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ) ; 
 int MBEDTLS_ERR_X509_INVALID_DATE ; 
 int /*<<< orphan*/  x509_date_is_valid (TYPE_1__*) ; 
 int /*<<< orphan*/  x509_parse_int (unsigned char**,int,int*) ; 

__attribute__((used)) static int x509_parse_time( unsigned char **p, size_t len, size_t yearlen,
        mbedtls_x509_time *time )
{
    int ret;

    /*
     * Minimum length is 10 or 12 depending on yearlen
     */
    if ( len < yearlen + 8 )
        return ( MBEDTLS_ERR_X509_INVALID_DATE );
    len -= yearlen + 8;

    /*
     * Parse year, month, day, hour, minute
     */
    CHECK( x509_parse_int( p, yearlen, &time->year ) );
    if ( 2 == yearlen )
    {
        if ( time->year < 50 )
            time->year += 100;

        time->year += 1900;
    }

    CHECK( x509_parse_int( p, 2, &time->mon ) );
    CHECK( x509_parse_int( p, 2, &time->day ) );
    CHECK( x509_parse_int( p, 2, &time->hour ) );
    CHECK( x509_parse_int( p, 2, &time->min ) );

    /*
     * Parse seconds if present
     */
    if ( len >= 2 )
    {
        CHECK( x509_parse_int( p, 2, &time->sec ) );
        len -= 2;
    }
    else
        return ( MBEDTLS_ERR_X509_INVALID_DATE );

    /*
     * Parse trailing 'Z' if present
     */
    if ( 1 == len && 'Z' == **p )
    {
        (*p)++;
        len--;
    }

    /*
     * We should have parsed all characters at this point
     */
    if ( 0 != len )
        return ( MBEDTLS_ERR_X509_INVALID_DATE );

    CHECK( x509_date_is_valid( time ) );

    return ( 0 );
}