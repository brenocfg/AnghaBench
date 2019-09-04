#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ppattr_cpu_attr_deadline; scalar_t__ ppattr_cpu_attr_interval; int /*<<< orphan*/  ppattr_cpu_percentage; int /*<<< orphan*/  ppattr_cpu_attr; } ;
typedef  TYPE_1__ proc_policy_cpuusage_attr_t ;
typedef  int /*<<< orphan*/  proc_policy_attribute_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_POLICY_ACTION_SET ; 
 int /*<<< orphan*/  PROC_POLICY_CPUMON_DEFAULTS ; 
 int /*<<< orphan*/  PROC_POLICY_RESOURCE_USAGE ; 
 int /*<<< orphan*/  PROC_POLICY_RSRCACT_NOTIFY_EXC ; 
 int /*<<< orphan*/  PROC_POLICY_RUSAGE_CPU ; 
 int /*<<< orphan*/  PROC_POLICY_SCOPE_PROCESS ; 
 int __process_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
proc_set_cpumon_defaults(pid_t pid)
{
	proc_policy_cpuusage_attr_t attr;

	attr.ppattr_cpu_attr = PROC_POLICY_RSRCACT_NOTIFY_EXC;
	attr.ppattr_cpu_percentage = PROC_POLICY_CPUMON_DEFAULTS;
	attr.ppattr_cpu_attr_interval = 0;
	attr.ppattr_cpu_attr_deadline = 0;

	return(__process_policy(PROC_POLICY_SCOPE_PROCESS, PROC_POLICY_ACTION_SET, PROC_POLICY_RESOURCE_USAGE,
		PROC_POLICY_RUSAGE_CPU, (proc_policy_attribute_t*)&attr, pid, 0));
}