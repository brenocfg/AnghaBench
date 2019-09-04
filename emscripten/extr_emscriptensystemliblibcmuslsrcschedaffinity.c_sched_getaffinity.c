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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int __syscall_ret (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_getaffinity (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 

int sched_getaffinity(pid_t tid, size_t size, cpu_set_t *set)
{
	return __syscall_ret(do_getaffinity(tid, size, set));
}