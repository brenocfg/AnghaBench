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
struct perf_target {int system_wide; int /*<<< orphan*/ * uid_str; scalar_t__ tid; int /*<<< orphan*/ * cpu_list; scalar_t__ pid; } ;
typedef  enum perf_target_errno { ____Placeholder_perf_target_errno } perf_target_errno ;

/* Variables and functions */
 int PERF_ERRNO_TARGET__PID_OVERRIDE_CPU ; 
 int PERF_ERRNO_TARGET__PID_OVERRIDE_SYSTEM ; 
 int PERF_ERRNO_TARGET__PID_OVERRIDE_UID ; 
 int PERF_ERRNO_TARGET__SUCCESS ; 
 int PERF_ERRNO_TARGET__UID_OVERRIDE_CPU ; 
 int PERF_ERRNO_TARGET__UID_OVERRIDE_SYSTEM ; 

enum perf_target_errno perf_target__validate(struct perf_target *target)
{
	enum perf_target_errno ret = PERF_ERRNO_TARGET__SUCCESS;

	if (target->pid)
		target->tid = target->pid;

	/* CPU and PID are mutually exclusive */
	if (target->tid && target->cpu_list) {
		target->cpu_list = NULL;
		if (ret == PERF_ERRNO_TARGET__SUCCESS)
			ret = PERF_ERRNO_TARGET__PID_OVERRIDE_CPU;
	}

	/* UID and PID are mutually exclusive */
	if (target->tid && target->uid_str) {
		target->uid_str = NULL;
		if (ret == PERF_ERRNO_TARGET__SUCCESS)
			ret = PERF_ERRNO_TARGET__PID_OVERRIDE_UID;
	}

	/* UID and CPU are mutually exclusive */
	if (target->uid_str && target->cpu_list) {
		target->cpu_list = NULL;
		if (ret == PERF_ERRNO_TARGET__SUCCESS)
			ret = PERF_ERRNO_TARGET__UID_OVERRIDE_CPU;
	}

	/* PID and SYSTEM are mutually exclusive */
	if (target->tid && target->system_wide) {
		target->system_wide = false;
		if (ret == PERF_ERRNO_TARGET__SUCCESS)
			ret = PERF_ERRNO_TARGET__PID_OVERRIDE_SYSTEM;
	}

	/* UID and SYSTEM are mutually exclusive */
	if (target->uid_str && target->system_wide) {
		target->system_wide = false;
		if (ret == PERF_ERRNO_TARGET__SUCCESS)
			ret = PERF_ERRNO_TARGET__UID_OVERRIDE_SYSTEM;
	}

	return ret;
}