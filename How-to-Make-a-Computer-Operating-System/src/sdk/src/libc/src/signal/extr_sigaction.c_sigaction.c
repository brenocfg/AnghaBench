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
struct sigaction {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_sigaction ; 
 int errno ; 
 int syscall3 (int /*<<< orphan*/ ,int,int,int) ; 

int sigaction( int signum, const struct sigaction* act, struct sigaction* oldact ) {
    int error;

    error = syscall3(
        SYS_sigaction,
        signum,
        ( int )act,
        ( int )oldact
    );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}