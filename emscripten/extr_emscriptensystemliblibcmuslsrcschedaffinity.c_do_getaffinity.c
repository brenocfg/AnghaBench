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
 int /*<<< orphan*/  SYS_sched_getaffinity ; 
 long __syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int do_getaffinity(pid_t tid, size_t size, cpu_set_t *set)
{
	long ret = __syscall(SYS_sched_getaffinity, tid, size, set);
	if (ret < 0) return ret;
	if (ret < size) memset((char *)set+ret, 0, size-ret);
	return 0;
}