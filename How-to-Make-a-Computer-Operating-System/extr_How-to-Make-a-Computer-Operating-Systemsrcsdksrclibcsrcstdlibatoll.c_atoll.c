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

long long int atoll( const char* s ) {
    long long int v = 0;
    int sign = 1;

    while ( *s == ' '  ||  ( unsigned int )( *s - 9 ) < 5u ) {
        ++s;
    }

    switch ( *s ) {
        case '-': sign = -1;
        case '+': ++s;
    }

    while ( ( unsigned int )( *s - '0' ) < 10u ) {
        v=  v * 10 + *s - '0';
        ++s;
    }

    return sign == -1 ? -v : v;
}