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
typedef  int suseconds_t ;
struct timeval {unsigned long tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  Sleep (unsigned long) ; 
 int /*<<< orphan*/  select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

void mbedtls_net_usleep( unsigned long usec )
{
#if defined(_WIN32)
    Sleep( ( usec + 999 ) / 1000 );
#else
    struct timeval tv;
    tv.tv_sec  = usec / 1000000;
#if defined(__unix__) || defined(__unix) || \
    ( defined(__APPLE__) && defined(__MACH__) )
    tv.tv_usec = (suseconds_t) usec % 1000000;
#else
    tv.tv_usec = usec % 1000000;
#endif
    select( 0, NULL, NULL, NULL, &tv );
#endif
}