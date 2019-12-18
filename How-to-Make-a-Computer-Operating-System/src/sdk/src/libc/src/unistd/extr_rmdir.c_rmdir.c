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
 int /*<<< orphan*/  SYS_rmdir ; 
 int errno ; 
 int syscall1 (int /*<<< orphan*/ ,int) ; 

int rmdir( const char* pathname ) {
    int error;

    error = syscall1( SYS_rmdir, ( int )pathname );

    if ( error < 0 ) {
        errno = -error;
        return -1;
    }

    return 0;
}