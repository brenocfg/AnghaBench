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

char* strncpy( char* d, const char* s, size_t c ) {
    size_t i;
    char* tmp = d;

    for ( i = 0; i < c; i++ ) {
        *d++ = *s;

        if ( *s++ == 0 ) {
            break;
        }
    }

    for ( ; i < c; i++ ) {
        *d++ = 0;
    }

    return tmp;
}