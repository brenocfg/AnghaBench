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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ task_t ;
struct pid_for_task_args {int t; int /*<<< orphan*/  pid; } ;
typedef  scalar_t__ proc_t ;
typedef  int mach_port_name_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int,int) ; 
 int /*<<< orphan*/  AUDIT_MACH_SYSCALL_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_MACH_SYSCALL_EXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUE_PIDFORTASK ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ TASK_NULL ; 
 int /*<<< orphan*/  copyout (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_bsdtask_info (scalar_t__) ; 
 scalar_t__ is_corpsetask (scalar_t__) ; 
 int mach_port1 ; 
 scalar_t__ port_name_to_task_inspect (int) ; 
 int proc_pid (scalar_t__) ; 
 int /*<<< orphan*/  task_deallocate (scalar_t__) ; 
 int task_pid (scalar_t__) ; 

kern_return_t
pid_for_task(
	struct pid_for_task_args *args)
{
	mach_port_name_t	t = args->t;
	user_addr_t		pid_addr  = args->pid;  
	proc_t p;
	task_t		t1;
	int	pid = -1;
	kern_return_t	err = KERN_SUCCESS;

	AUDIT_MACH_SYSCALL_ENTER(AUE_PIDFORTASK);
	AUDIT_ARG(mach_port1, t);

	t1 = port_name_to_task_inspect(t);

	if (t1 == TASK_NULL) {
		err = KERN_FAILURE;
		goto pftout;
	} else {
		p = get_bsdtask_info(t1);
		if (p) {
			pid  = proc_pid(p);
			err = KERN_SUCCESS;
		} else if (is_corpsetask(t1)) {
			pid = task_pid(t1);
			err = KERN_SUCCESS;
		}else {
			err = KERN_FAILURE;
		}
	}
	task_deallocate(t1);
pftout:
	AUDIT_ARG(pid, pid);
	(void) copyout((char *) &pid, pid_addr, sizeof(int));
	AUDIT_MACH_SYSCALL_EXIT(err);
	return(err);
}