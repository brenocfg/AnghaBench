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
 int strlen (char const*) ; 

char* strpbrk( const char* s, const char* accept ) {
    register int i, l = strlen( accept );

    for ( ; *s != 0; s++ )
        for ( i = 0; i < l; i++ )
            if (*s == accept[i])
                return (char*)s;

    return 0;
}