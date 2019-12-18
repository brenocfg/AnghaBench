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

/* Variables and functions */
 int /*<<< orphan*/  SYS_mount ; 
 int errno ; 
 int syscall4 (int /*<<< orphan*/ ,int,int,int,int) ; 

int mount(
    const char* source,
    const char* target,
    const char* filesystemtype,
    unsigned long mountflags,
    const void* data
) {
    int error;

    error = syscall4(
        SYS_mount,
        ( int )source,
        ( int )target,
        ( int )filesystemtype,
        ( int )mountflags
    );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}