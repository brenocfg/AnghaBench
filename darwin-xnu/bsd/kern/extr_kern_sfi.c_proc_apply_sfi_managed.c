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
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ pid_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {scalar_t__ p_pid; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  DBG_MACH_SFI ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PROC_RETURNED ; 
 int /*<<< orphan*/  SFI_PID_CLEAR_MANAGED ; 
 int /*<<< orphan*/  SFI_PID_SET_MANAGED ; 
 scalar_t__ SFI_PROCESS_SET_MANAGED ; 
 int /*<<< orphan*/  TASK_POLICY_ATTRIBUTE ; 
 int /*<<< orphan*/  TASK_POLICY_DISABLE ; 
 int /*<<< orphan*/  TASK_POLICY_ENABLE ; 
 int /*<<< orphan*/  TASK_POLICY_SFI_MANAGED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  proc_set_task_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_apply_sfi_managed(proc_t p, void * arg)
{
	uint32_t flags = *(uint32_t *)arg;
	pid_t pid = p->p_pid;
	boolean_t managed_enabled = (flags == SFI_PROCESS_SET_MANAGED)? TRUE : FALSE;
	
	if (pid == 0) {		/* ignore setting on kernproc */
		return PROC_RETURNED;
	}

	if (managed_enabled) {
		KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_SFI, SFI_PID_SET_MANAGED) | DBG_FUNC_NONE, pid, 0, 0, 0, 0);
	} else {
		KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_SFI, SFI_PID_CLEAR_MANAGED) | DBG_FUNC_NONE, pid, 0, 0, 0, 0);
	}

	proc_set_task_policy(p->task,
	                     TASK_POLICY_ATTRIBUTE, TASK_POLICY_SFI_MANAGED,
	                     managed_enabled ? TASK_POLICY_ENABLE : TASK_POLICY_DISABLE);

	return PROC_RETURNED;
}