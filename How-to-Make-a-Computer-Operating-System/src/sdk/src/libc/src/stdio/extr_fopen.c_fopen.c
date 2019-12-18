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
 int /*<<< orphan*/ * __init_file (int,int,int) ; 
 int __parse_mode (char const*) ; 
 int open (char const*,int,int) ; 

FILE* fopen( const char* path, const char* mode ) {
    int fd;
    int flags;

    flags = __parse_mode( mode );

    fd = open( path, flags, 0666 );

    if ( fd < 0 ) {
        return NULL;
    }

    return __init_file( fd, 1, flags );
}