#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ task_t ;
struct task_name_for_pid_args {int pid; int /*<<< orphan*/  t; TYPE_1__* target_tport; } ;
typedef  TYPE_1__* proc_t ;
typedef  TYPE_1__* mach_port_name_t ;
typedef  int kern_return_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_12__ {scalar_t__ p_stat; scalar_t__ task; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int,...) ; 
 int /*<<< orphan*/  AUDIT_MACH_SYSCALL_ENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_MACH_SYSCALL_EXIT (int) ; 
 int /*<<< orphan*/  AUE_TASKNAMEFORPID ; 
 int KERN_FAILURE ; 
 int KERN_SUCCESS ; 
 TYPE_1__* MACH_PORT_NULL ; 
 TYPE_1__* PROC_NULL ; 
 scalar_t__ SZOMB ; 
 scalar_t__ TASK_NULL ; 
 scalar_t__ convert_task_name_to_port (scalar_t__) ; 
 int /*<<< orphan*/  copyout (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  get_task_ipcspace (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipc_port_copyout_send (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 scalar_t__ kauth_cred_getruid (int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_proc_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ kauth_getruid () ; 
 int mac_proc_check_get_task_name (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mach_port1 ; 
 int /*<<< orphan*/  mach_port2 ; 
 scalar_t__ port_name_to_task (TYPE_1__*) ; 
 TYPE_1__* proc_find (int) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  process ; 
 int /*<<< orphan*/  task_deallocate (scalar_t__) ; 
 int /*<<< orphan*/  task_reference (scalar_t__) ; 

kern_return_t
task_name_for_pid(
	struct task_name_for_pid_args *args)
{
	mach_port_name_t	target_tport = args->target_tport;
	int			pid = args->pid;
	user_addr_t		task_addr = args->t;
	proc_t		p = PROC_NULL;
	task_t		t1;
	mach_port_name_t	tret;
	void * sright;
	int error = 0, refheld = 0;
	kauth_cred_t target_cred;

	AUDIT_MACH_SYSCALL_ENTER(AUE_TASKNAMEFORPID);
	AUDIT_ARG(pid, pid);
	AUDIT_ARG(mach_port1, target_tport);

	t1 = port_name_to_task(target_tport);
	if (t1 == TASK_NULL) {
		(void) copyout((char *)&t1, task_addr, sizeof(mach_port_name_t));
		AUDIT_MACH_SYSCALL_EXIT(KERN_FAILURE);
		return(KERN_FAILURE);
	} 

	p = proc_find(pid);
	if (p != PROC_NULL) {
		AUDIT_ARG(process, p);
		target_cred = kauth_cred_proc_ref(p);
		refheld = 1;

		if ((p->p_stat != SZOMB)
		    && ((current_proc() == p)
			|| kauth_cred_issuser(kauth_cred_get()) 
			|| ((kauth_cred_getuid(target_cred) == kauth_cred_getuid(kauth_cred_get())) && 
			    ((kauth_cred_getruid(target_cred) == kauth_getruid()))))) {

			if (p->task != TASK_NULL) {
				task_reference(p->task);
#if CONFIG_MACF
				error = mac_proc_check_get_task_name(kauth_cred_get(),  p);
				if (error) {
					task_deallocate(p->task);
					goto noperm;
				}
#endif
				sright = (void *)convert_task_name_to_port(p->task);
				tret = ipc_port_copyout_send(sright, 
						get_task_ipcspace(current_task()));
			} else
				tret  = MACH_PORT_NULL;

			AUDIT_ARG(mach_port2, tret);
			(void) copyout((char *)&tret, task_addr, sizeof(mach_port_name_t));
			task_deallocate(t1);
			error = KERN_SUCCESS;
			goto tnfpout;
		}
	}

#if CONFIG_MACF
noperm:
#endif
    task_deallocate(t1);
	tret = MACH_PORT_NULL;
	(void) copyout((char *) &tret, task_addr, sizeof(mach_port_name_t));
	error = KERN_FAILURE;
tnfpout:
	if (refheld != 0)
		kauth_cred_unref(&target_cred);
	if (p != PROC_NULL)
		proc_rele(p);
	AUDIT_MACH_SYSCALL_EXIT(error);
	return(error);
}