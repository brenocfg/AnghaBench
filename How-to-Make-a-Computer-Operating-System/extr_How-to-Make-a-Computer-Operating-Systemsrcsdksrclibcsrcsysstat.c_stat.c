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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_stat ; 
 int errno ; 
 int syscall2 (int /*<<< orphan*/ ,int,int) ; 

int stat( const char* path, struct stat* stat ) {
    int error;

    error = syscall2( SYS_stat, ( int )path, ( int )stat );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}