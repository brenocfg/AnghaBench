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
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigtimedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 

int
main(void)
{

    sigset_t set;
    siginfo_t info;
    struct timespec timeout;

    (void)sigemptyset(&set);
    (void)sigaddset(&set, SIGHUP);
    timeout.tv_sec = 1;
    timeout.tv_nsec = 0;

    for (;;)
        (void)sigtimedwait(&set, &info, &timeout);

    return (0);
}