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
 scalar_t__ EEXIST ; 
 scalar_t__ EINVAL ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_NOFOLLOW ; 
 int O_RDWR ; 
 scalar_t__ errno ; 
 int open (char*,int,int) ; 
 unsigned int random () ; 
 int strlen (char*) ; 

int mkstemp( char* template ) {
    int i;
    char* tmp;
    int result;
    unsigned int rnd;

    tmp = template + strlen( template ) - 6;

    if ( tmp < template ) {
        errno = EINVAL;
        return -1;
    }

    for ( i = 0; i < 6; i++ ) {
        if ( tmp[ i ] != 'X' ) {
            errno = EINVAL;
            return -1;
        }
    }

    for ( ;; ) {
        for ( i = 0; i < 6; i++ ) {
            int hexdigit;

            rnd = random();
            hexdigit = ( rnd >> ( i * 5 ) ) & 0x1F;
            tmp[ i ] = hexdigit > 9 ? ( hexdigit + 'a' - 10 ) : ( hexdigit + '0' );
        }

        result = open( template, O_CREAT | O_RDWR | O_EXCL | O_NOFOLLOW, 0600 );

        if ( ( result >= 0 ) ||
             ( errno != EEXIST ) ) {
            break;
        }
    }

    return result;
}