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
struct rusage {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_wait4 ; 
 int errno ; 
 int syscall4 (int /*<<< orphan*/ ,int,int,int,int) ; 

pid_t wait4( pid_t pid, int* status, int options, struct rusage* rusage ) {
    int error;

    error = syscall4(
        SYS_wait4,
        pid,
        ( int )status,
        options,
        ( int )rusage
    );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return error;
}