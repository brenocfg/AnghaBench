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

void* memchr( const void* s, int c, size_t n ) {
    const unsigned char* src = ( const unsigned char* )s;
    unsigned char ch = c;

    for ( ; n != 0; n-- ) {
        if ( *src == ch ) {
            return ( void* )src;
        }

        src++;
    }

    return NULL;
}