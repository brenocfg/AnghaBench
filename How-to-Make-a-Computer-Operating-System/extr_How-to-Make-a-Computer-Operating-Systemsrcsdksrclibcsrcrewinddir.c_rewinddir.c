#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_rewinddir ; 
 int errno ; 
 int syscall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rewinddir( DIR* dirp ) {
    int error;

    error = syscall1( SYS_rewinddir, dirp->fd );

    if ( error < 0 ) {
        errno = -error;
    }
}