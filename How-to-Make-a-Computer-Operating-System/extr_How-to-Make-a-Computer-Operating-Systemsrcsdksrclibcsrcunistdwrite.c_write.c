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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_write ; 
 int errno ; 
 int syscall3 (int /*<<< orphan*/ ,int,int,size_t) ; 

ssize_t write( int fd, const void* buf, size_t count ) {
    int error;

    error = syscall3( SYS_write, fd, ( int )buf, count );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}