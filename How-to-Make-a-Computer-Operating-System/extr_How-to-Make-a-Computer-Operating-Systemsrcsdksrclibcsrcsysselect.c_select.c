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
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_select ; 
 int errno ; 
 int syscall5 (int /*<<< orphan*/ ,int,int,int,int,int) ; 

int select( int fds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout ) {
    int error;

    error = syscall5(
        SYS_select,
        fds,
        ( int )readfds,
        ( int )writefds,
        ( int )exceptfds,
        ( int )timeout
    );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}