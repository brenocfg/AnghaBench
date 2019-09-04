#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int tv_sec; int /*<<< orphan*/  tv_usec; } ;
struct itimerval {TYPE_1__ it_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  SYS_setitimer ; 
 int /*<<< orphan*/  __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerval*,struct itimerval*) ; 

unsigned alarm(unsigned seconds)
{
	struct itimerval it = { .it_value.tv_sec = seconds };
	__syscall(SYS_setitimer, ITIMER_REAL, &it, &it);
	return it.it_value.tv_sec + !!it.it_value.tv_usec;
}