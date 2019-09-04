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
struct itimerspec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_timerfd_settime ; 
 int syscall (int /*<<< orphan*/ ,int,int,struct itimerspec const*,struct itimerspec*) ; 

int timerfd_settime(int fd, int flags, const struct itimerspec *new, struct itimerspec *old)
{
	return syscall(SYS_timerfd_settime, fd, flags, new, old);
}