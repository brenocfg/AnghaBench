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
 size_t MIN (size_t,size_t) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

char* strndup( const char* s, size_t n ) {
    char* s2;
    size_t len;

    len = strlen( s );
    len = MIN( len, n );

    s2 = ( char* )malloc( len + 1 );

    if ( s2 == NULL ) {
        return NULL;
    }

    memcpy( s2, s, len );
    s2[ len ] = '\0';

    return s2;
}