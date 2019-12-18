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
 scalar_t__ islower (char const) ; 
 char const toupper (char const) ; 

__attribute__((used)) static char* strncpyupper( char *dst, const char *src, int len )
{
    int ii;

    for ( ii = 0; ii < len-1 && src[ii]; ii++ )
    {
        dst[ii] = islower(src[ii]) ? toupper(src[ii]) : src[ii];
    }
    dst[ii] = '\0';
    return dst;
}