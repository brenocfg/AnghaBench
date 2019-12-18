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

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_LDT ; 
 long errno ; 
 int ptrace (int /*<<< orphan*/ ,long,long,long) ; 

long os_ptrace_ldt(long pid, long addr, long data)
{
	int ret;

	ret = ptrace(PTRACE_LDT, pid, addr, data);

	if (ret < 0)
		return -errno;
	return ret;
}