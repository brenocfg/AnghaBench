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
struct task_struct {int flags; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int PF_MCE_EARLY ; 
 int PF_MCE_PROCESS ; 
 int sysctl_memory_failure_early_kill ; 

__attribute__((used)) static int task_early_kill(struct task_struct *tsk)
{
	if (!tsk->mm)
		return 0;
	if (tsk->flags & PF_MCE_PROCESS)
		return !!(tsk->flags & PF_MCE_EARLY);
	return sysctl_memory_failure_early_kill;
}