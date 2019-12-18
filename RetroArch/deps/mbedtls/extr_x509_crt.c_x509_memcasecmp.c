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

__attribute__((used)) static int x509_memcasecmp( const void *s1, const void *s2, size_t len )
{
    size_t i;
    unsigned char diff;
    const unsigned char *n1 = s1, *n2 = s2;

    for( i = 0; i < len; i++ )
    {
        diff = n1[i] ^ n2[i];

        if( diff == 0 )
            continue;

        if( diff == 32 &&
            ( ( n1[i] >= 'a' && n1[i] <= 'z' ) ||
              ( n1[i] >= 'A' && n1[i] <= 'Z' ) ) )
        {
            continue;
        }

        return( -1 );
    }

    return( 0 );
}