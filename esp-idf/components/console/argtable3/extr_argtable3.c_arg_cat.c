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

__attribute__((used)) static
void arg_cat(char * *pdest, const char *src, size_t *pndest)
{
    char *dest = *pdest;
    char *end  = dest + *pndest;

    /*locate null terminator of dest string */
    while(dest < end && *dest != 0)
        dest++;

    /* concat src string to dest string */
    while(dest < end && *src != 0)
        *dest++ = *src++;

    /* null terminate dest string */
    *dest = 0;

    /* update *pdest and *pndest */
    *pndest = end - dest;
    *pdest  = dest;
}