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
typedef  unsigned long long sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int _NSIG ; 
 int /*<<< orphan*/  errno ; 

int sigismember( const sigset_t* set, int signum ) {
    if ( ( set == NULL ) ||
         ( signum < 1 ) ||
         ( signum >= _NSIG ) ) {
        errno = -EINVAL;
        return -1;
    }

    if ( ( ( *set ) & ( 1ULL << ( signum - 1 ) ) ) != 0 ) {
        return 1;
    }

    return 0;
}