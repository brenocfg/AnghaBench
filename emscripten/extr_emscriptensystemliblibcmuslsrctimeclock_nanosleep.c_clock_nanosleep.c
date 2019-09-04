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
 int /*<<< orphan*/  SYS_clock_nanosleep ; 
 int __syscall_cp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct timespec const*,struct timespec*) ; 

int clock_nanosleep(clockid_t clk, int flags, const struct timespec *req, struct timespec *rem)
{
	return -__syscall_cp(SYS_clock_nanosleep, clk, flags, req, rem);
}