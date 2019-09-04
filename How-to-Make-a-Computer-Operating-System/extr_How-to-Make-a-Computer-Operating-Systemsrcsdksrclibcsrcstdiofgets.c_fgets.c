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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 

char* fgets( char* s, int size, FILE* stream ) {
    char* orig = s;
    int l;

    for ( l = size; l > 1; ) {
        register int c = fgetc( stream );
		//printf("c:  %c \n");
        if ( c == EOF ) {
            break;
        }

        *s = c;
        ++s;
        --l;

        if ( c == '\n' ) {
            break;
        }
    }

    if ( ( l == size ) || ( ferror( stream ) ) ) {
        return 0;
    }

    *s = 0;

    return orig;
}