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
 scalar_t__ PULLUP_ABS (unsigned char) ; 

__attribute__((used)) static int pullup_diff_y( unsigned char  *a, unsigned char * b, int s )
{
    int i, j, diff = 0;
    for( i = 4; i; i-- )
    {
        for( j = 0; j < 8; j++ )
        {
            diff += PULLUP_ABS( a[j]-b[j] );
        }
        a+=s; b+=s;
    }
    return diff;
}