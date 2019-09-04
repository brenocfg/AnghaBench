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

void* memmove( void* dest, const void* src, size_t n ) {
    char* _dest;
    char* _src;

    if ( dest < src ) {
        _dest = ( char* )dest;
        _src = ( char* )src;

        while ( n-- ) {
            *_dest++ = *_src++;
        }
    } else {
        _dest = ( char* )dest + n;
        _src = ( char* )src + n;

        while ( n-- ) {
            *--_dest = *--_src;
        }
    }

    return dest;
}