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
typedef  int pid_t ;
typedef  int clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_clock_getres ; 
 int __syscall (int /*<<< orphan*/ ,int,struct timespec*) ; 

int clock_getcpuclockid(pid_t pid, clockid_t *clk)
{
	struct timespec ts;
	clockid_t id = (-pid-1)*8U + 2;
	int ret = __syscall(SYS_clock_getres, id, &ts);
	if (ret) return -ret;
	*clk = id;
	return 0;
}