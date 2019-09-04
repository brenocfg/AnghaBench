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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_pwrite ; 
 int errno ; 
 int syscall4 (int /*<<< orphan*/ ,int,int,size_t,int) ; 

ssize_t pwrite( int fd, const void* buf, size_t count, off_t offset ) {
    int error;

    error = syscall4( SYS_pwrite, fd, ( int )buf, count, ( int )&offset );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}