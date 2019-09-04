#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_5__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 TYPE_1__* PROC_NULL ; 
 int /*<<< orphan*/  TASK_POLICY_DARWIN_BG ; 
 TYPE_1__* proc_find (int /*<<< orphan*/ ) ; 
 scalar_t__ proc_get_effective_task_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 

int
proc_pidbackgrounded(pid_t pid, uint32_t* state)
{
	proc_t target_proc = PROC_NULL;

	if (state == NULL)
		return(EINVAL);	

	target_proc = proc_find(pid);

	if (target_proc == PROC_NULL)
		return(ESRCH);

	if ( proc_get_effective_task_policy(target_proc->task, TASK_POLICY_DARWIN_BG) ) {
		*state = 1;
	} else {
		*state = 0;
	}

	proc_rele(target_proc);
	return (0);
}