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
 int /*<<< orphan*/  strcspn (char*,char const*) ; 
 int /*<<< orphan*/  strspn (char*,char const*) ; 

char* strtok_r( char* s, const char* delim, char** ptrptr ) {
    char* tmp = NULL;

    if ( s == NULL ) {
        s = *ptrptr;
    }

    s += strspn( s, delim );

    if ( *s ) {
        tmp = s;
        s += strcspn( s, delim );

        if ( *s ) {
            *s++ = 0;
        }
    }

    *ptrptr = s;

    return tmp;
}