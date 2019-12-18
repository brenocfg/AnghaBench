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
typedef  int /*<<< orphan*/  rusage_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_INFO_CALL_PIDRUSAGE ; 
 int __proc_info (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
proc_pid_rusage(int pid, int flavor, rusage_info_t *buffer)
{
	return (__proc_info(PROC_INFO_CALL_PIDRUSAGE, pid, flavor, 0, buffer, 0));
}