#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ task_t ;
struct task_for_pid_args {int pid; int /*<<< orphan*/  t; TYPE_1__* target_tport; } ;
typedef  TYPE_1__* proc_t ;
typedef  TYPE_1__* mach_port_name_t ;
typedef  int kern_return_t ;
typedef  scalar_t__ ipc_port_t ;
struct TYPE_11__ {scalar_t__ task; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int,...) ; 
 int /*<<< orphan*/  AUDIT_MACH_SYSCALL_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_MACH_SYSCALL_EXIT (int) ; 
 int /*<<< orphan*/  AUE_TASKFORPID ; 
 scalar_t__ IPC_PORT_DEAD ; 
 scalar_t__ IPC_PORT_NULL ; 
 int KERN_ABORTED ; 
 int KERN_FAILURE ; 
 int KERN_PROTECTION_FAILURE ; 
 int KERN_SUCCESS ; 
 int MACH_MSG_SUCCESS ; 
 void* MACH_PORT_NULL ; 
 int MACH_RCV_INTERRUPTED ; 
 TYPE_1__* PROC_NULL ; 
 scalar_t__ TASK_NULL ; 
 int __KERNEL_WAITING_ON_TASKGATED_CHECK_ACCESS_UPCALL__ (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ convert_task_to_port (scalar_t__) ; 
 int /*<<< orphan*/  copyout (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  extmod_statistics_incr_task_for_pid (scalar_t__) ; 
 int /*<<< orphan*/  get_task_ipcspace (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipc_port_copyout_send (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_port_release_send (scalar_t__) ; 
 scalar_t__ is_corpsetask (scalar_t__) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_getgid () ; 
 int mac_proc_check_get_task (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mach_port1 ; 
 int /*<<< orphan*/  mach_port2 ; 
 scalar_t__ port_name_to_task (TYPE_1__*) ; 
 TYPE_1__* proc_find (int) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_selfpid () ; 
 int /*<<< orphan*/  process ; 
 int /*<<< orphan*/  task_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  task_for_pid_posix_check (TYPE_1__*) ; 
 scalar_t__ task_get_task_access_port (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  task_reference (scalar_t__) ; 

kern_return_t
task_for_pid(
	struct task_for_pid_args *args)
{
	mach_port_name_t	target_tport = args->target_tport;
	int			pid = args->pid;
	user_addr_t		task_addr = args->t;
	proc_t 			p = PROC_NULL;
	task_t			t1 = TASK_NULL;
	task_t			task = TASK_NULL;
	mach_port_name_t	tret = MACH_PORT_NULL;
	ipc_port_t 		tfpport = MACH_PORT_NULL;
	void * sright;
	int error = 0;

	AUDIT_MACH_SYSCALL_ENTER(AUE_TASKFORPID);
	AUDIT_ARG(pid, pid);
	AUDIT_ARG(mach_port1, target_tport);

	/* Always check if pid == 0 */
	if (pid == 0) {
		(void ) copyout((char *)&t1, task_addr, sizeof(mach_port_name_t));
		AUDIT_MACH_SYSCALL_EXIT(KERN_FAILURE);
		return(KERN_FAILURE);
	}

	t1 = port_name_to_task(target_tport);
	if (t1 == TASK_NULL) {
		(void) copyout((char *)&t1, task_addr, sizeof(mach_port_name_t));
		AUDIT_MACH_SYSCALL_EXIT(KERN_FAILURE);
		return(KERN_FAILURE);
	} 


	p = proc_find(pid);
	if (p == PROC_NULL) {
		error = KERN_FAILURE;
		goto tfpout;
	}

#if CONFIG_AUDIT
	AUDIT_ARG(process, p);
#endif

	if (!(task_for_pid_posix_check(p))) {
		error = KERN_FAILURE;
		goto tfpout;
	}

	if (p->task == TASK_NULL) {
		error = KERN_SUCCESS;
		goto tfpout;
	}

#if CONFIG_MACF
	error = mac_proc_check_get_task(kauth_cred_get(), p);
	if (error) {
		error = KERN_FAILURE;
		goto tfpout;
	}
#endif

	/* Grab a task reference since the proc ref might be dropped if an upcall to task access server is made */
	task = p->task;
	task_reference(task);

	/* If we aren't root and target's task access port is set... */
	if (!kauth_cred_issuser(kauth_cred_get()) &&
		p != current_proc() &&
		(task_get_task_access_port(task, &tfpport) == 0) &&
		(tfpport != IPC_PORT_NULL)) {

		if (tfpport == IPC_PORT_DEAD) {
			error = KERN_PROTECTION_FAILURE;
			goto tfpout;
		}

		/*
		 * Drop the proc_find proc ref before making an upcall
		 * to taskgated, since holding a proc_find
		 * ref while making an upcall can cause deadlock.
		 */
		proc_rele(p);
		p = PROC_NULL;

		/* Call up to the task access server */
		error = __KERNEL_WAITING_ON_TASKGATED_CHECK_ACCESS_UPCALL__(tfpport, proc_selfpid(), kauth_getgid(), pid);

		if (error != MACH_MSG_SUCCESS) {
			if (error == MACH_RCV_INTERRUPTED)
				error = KERN_ABORTED;
			else
				error = KERN_FAILURE;
			goto tfpout;
		}
	}

	/* Grant task port access */
	extmod_statistics_incr_task_for_pid(task);
	sright = (void *) convert_task_to_port(task);

	/* Check if the task has been corpsified */
	if (is_corpsetask(task)) {
		/* task ref consumed by convert_task_to_port */
		task = TASK_NULL;
		ipc_port_release_send(sright);
		error = KERN_FAILURE;
		goto tfpout;
	}

	/* task ref consumed by convert_task_to_port */
	task = TASK_NULL;
	tret = ipc_port_copyout_send(
			sright,
			get_task_ipcspace(current_task()));

	error = KERN_SUCCESS;

tfpout:
	task_deallocate(t1);
	AUDIT_ARG(mach_port2, tret);
	(void) copyout((char *) &tret, task_addr, sizeof(mach_port_name_t));

	if (tfpport != IPC_PORT_NULL) {
		ipc_port_release_send(tfpport);
	}
	if (task != TASK_NULL) {
		task_deallocate(task);
	}
	if (p != PROC_NULL)
		proc_rele(p);
	AUDIT_MACH_SYSCALL_EXIT(error);
	return(error);
}