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

int memcmp( const void* p1, const void* p2, size_t c ) {
    const unsigned char* su1, *su2;
    signed char res = 0;

    for ( su1 = p1, su2 = p2; 0 < c; ++su1, ++su2, c-- ) {
        if ( ( res = *su1 - *su2 ) != 0 ) {
            break;
        }
    }

    return res;
}