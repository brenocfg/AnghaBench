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
struct utimbuf {int /*<<< orphan*/  actime; int /*<<< orphan*/  modtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_utime ; 
 int errno ; 
 int syscall2 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int utime( const char* filename, const struct utimbuf* times ) {
    int error;
    struct utimbuf current;

    if ( times == NULL ) {
        current.actime = time( NULL );
        current.modtime = current.actime;

        times = ( const struct utimbuf* )&current;
    }

    error = syscall2( SYS_utime, ( int )filename, ( int )times  );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}