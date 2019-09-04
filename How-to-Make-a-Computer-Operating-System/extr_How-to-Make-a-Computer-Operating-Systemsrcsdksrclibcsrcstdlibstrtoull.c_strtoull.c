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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int ULLONG_MAX ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ isspace (char const) ; 
 scalar_t__ isxdigit (char const) ; 

unsigned long long int strtoull( const char* ptr, char** endptr, int base ) {
    int neg = 0, overflow = 0;
    long long int v = 0;
    const char* orig;
    const char* nptr = ptr;

    while ( isspace( *nptr ) ) {
        ++nptr;
    }

    if ( *nptr == '-' ) {
        neg=1;
        nptr++;
    } else if ( *nptr == '+' ) {
        ++nptr;
    }

    orig = nptr;

    if ( ( base == 16 ) && ( nptr[ 0 ] == '0' ) ) {
        goto skip0x;
    }

    if ( base ) {
        register unsigned int b = base - 2;

        if ( b > 34 ) {
            errno = EINVAL;
            return 0;
        }
    } else {
        if ( *nptr == '0' ) {
            base = 8;

skip0x:
            if ( ( ( *( nptr + 1 ) == 'x' ) || ( *( nptr + 1 ) == 'X' ) ) && isxdigit( nptr[ 2 ] ) ) {
                nptr += 2;
                base = 16;
            }
        } else {
            base = 10;
        }
    }

    while ( *nptr ) {
        register unsigned char c = *nptr;

        c = ( c >= 'a' ? c - 'a' + 10 : c >= 'A' ? c - 'A' + 10 : c <= '9' ? c - '0' : 0xFF );

        if ( c >= base ) {
            break;	/* out of base */
        }

        {
            register unsigned long x = ( v & 0xFF ) * base + c;
            register unsigned long long w = ( v >> 8 ) * base + ( x >> 8 );

            if ( w > ( ULLONG_MAX >> 8 ) ) {
                overflow = 1;
            }

            v = ( w << 8 ) + ( x & 0xFF );
        }

        ++nptr;
    }

    if ( nptr == orig ) {		/* no conversion done */
        nptr = ptr;
        errno = EINVAL;
        v = 0;
    }

    if ( endptr != NULL ) {
        *endptr = (char *)nptr;
    }

    if ( overflow ) {
        errno = ERANGE;
        return ULLONG_MAX;
    }

    return ( neg ? -v : v );
}