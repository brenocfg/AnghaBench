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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (void*,int,int) ; 

int sigfillset( sigset_t* set ) {
    if ( set == NULL ) {
        errno = -EINVAL;
        return -1;
    }

    memset( ( void* )set, 0xFF, sizeof( sigset_t ) );

    return 0;
}