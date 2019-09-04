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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_POLICY_ACTION_RESTORE ; 
 int /*<<< orphan*/  PROC_POLICY_RESOURCE_USAGE ; 
 int /*<<< orphan*/  PROC_POLICY_RUSAGE_CPU ; 
 int /*<<< orphan*/  PROC_POLICY_SCOPE_PROCESS ; 
 int __process_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 

int
proc_clear_cpulimits(pid_t pid)
{
	if (__process_policy(PROC_POLICY_SCOPE_PROCESS, PROC_POLICY_ACTION_RESTORE, PROC_POLICY_RESOURCE_USAGE, PROC_POLICY_RUSAGE_CPU, NULL, pid, (uint64_t)0) != -1)
		return(0);
	else
		return(errno);
}