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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_connect ; 
 int errno ; 
 int syscall3 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int connect( int fd, const struct sockaddr* address, socklen_t addrlen ) {
    int error;

    error = syscall3( SYS_connect, fd, ( int )address, addrlen );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}