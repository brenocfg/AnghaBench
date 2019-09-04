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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_sched_rr_get_interval ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*) ; 

int sched_rr_get_interval(pid_t pid, struct timespec *ts)
{
	return syscall(SYS_sched_rr_get_interval, pid, ts);
}