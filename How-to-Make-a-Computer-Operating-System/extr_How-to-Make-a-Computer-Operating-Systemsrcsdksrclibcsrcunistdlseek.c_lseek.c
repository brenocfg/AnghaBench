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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_lseek ; 
 int errno ; 
 int syscall4 (int /*<<< orphan*/ ,int,int,int,int) ; 

off_t lseek( int fd, off_t offset, int whence ) {
    int error;
    off_t result;

    error = syscall4( SYS_lseek, fd, ( int )&offset, whence, ( int )&result );

    if ( error < 0 ) {
        errno = -error;
        return ( off_t )-1;
    }

    return result;
}