#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int ppattr_cpu_attr; int ppattr_cpu_percentage; } ;
typedef  TYPE_1__ proc_policy_cpuusage_attr_t ;
typedef  int /*<<< orphan*/  proc_policy_attribute_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_POLICY_ACTION_APPLY ; 
 int /*<<< orphan*/  PROC_POLICY_RESOURCE_USAGE ; 
 int /*<<< orphan*/  PROC_POLICY_RUSAGE_CPU ; 
 int /*<<< orphan*/  PROC_POLICY_SCOPE_PROCESS ; 
 int __process_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int errno ; 

int 
proc_setcpu_percentage(pid_t pid, int action, int percentage)
{
	proc_policy_cpuusage_attr_t attr;

	bzero(&attr, sizeof(proc_policy_cpuusage_attr_t));
	attr.ppattr_cpu_attr = action;
	attr.ppattr_cpu_percentage = percentage;
	if (__process_policy(PROC_POLICY_SCOPE_PROCESS, PROC_POLICY_ACTION_APPLY, PROC_POLICY_RESOURCE_USAGE, PROC_POLICY_RUSAGE_CPU, (proc_policy_attribute_t*)&attr, pid, (uint64_t)0) != -1)
		return(0);
	else
		return(errno);
}