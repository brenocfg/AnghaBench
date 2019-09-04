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
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_clock_getres ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*) ; 

int clock_getres(clockid_t clk, struct timespec *ts)
{
	return syscall(SYS_clock_getres, clk, ts);
}