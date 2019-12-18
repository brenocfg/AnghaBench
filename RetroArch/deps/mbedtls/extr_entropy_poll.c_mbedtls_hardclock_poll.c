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
 unsigned long mbedtls_timing_hardclock () ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned long*,int) ; 

int mbedtls_hardclock_poll( void *data,
                    unsigned char *output, size_t len, size_t *olen )
{
    unsigned long timer = mbedtls_timing_hardclock();
    ((void) data);
    *olen = 0;

    if( len < sizeof(unsigned long) )
        return( 0 );

    memcpy( output, &timer, sizeof(unsigned long) );
    *olen = sizeof(unsigned long);

    return( 0 );
}