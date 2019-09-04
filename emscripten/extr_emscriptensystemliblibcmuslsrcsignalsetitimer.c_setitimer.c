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
struct itimerval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_setitimer ; 
 int syscall (int /*<<< orphan*/ ,int,struct itimerval const*,struct itimerval*) ; 

int setitimer(int which, const struct itimerval *restrict new, struct itimerval *restrict old)
{
	return syscall(SYS_setitimer, which, new, old);
}