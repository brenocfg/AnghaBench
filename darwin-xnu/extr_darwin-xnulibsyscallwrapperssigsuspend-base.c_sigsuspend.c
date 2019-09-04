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
 int __SIGSUSPEND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

int
sigsuspend (const sigset_t *sigmask_p)
{
    sigset_t	mask;

    if (sigmask_p)
        mask = *sigmask_p;
    else
        sigemptyset(&mask);
    return __SIGSUSPEND(mask);
}