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
typedef  TYPE_1__* proc_t ;
struct TYPE_12__ {int p_lflag; int p_pid; char* p_comm; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int ESRCH ; 
 scalar_t__ PROC_ACTION_STATE (TYPE_1__*) ; 
 int PROC_CONTROL_STATE (TYPE_1__*) ; 
 TYPE_1__* PROC_NULL ; 
 int /*<<< orphan*/  PROC_RESETACTION_STATE (TYPE_1__*) ; 
 int /*<<< orphan*/  PROC_SETACTION_STATE (TYPE_1__*) ; 
 int P_LVMRSRCOWNER ; 
#define  P_PCKILL 130 
#define  P_PCSUSP 129 
#define  P_PCTHROTTLE 128 
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 TYPE_1__* proc_find (int) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 
 int suser (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_resume (int /*<<< orphan*/ ) ; 

int
proc_resetpcontrol(int pid)
{
	proc_t p;
	int pcontrol;
	int error;
	proc_t self = current_proc();

	/* if the process has been validated to handle resource control or root is valid one */
	if (((self->p_lflag & P_LVMRSRCOWNER) == 0) && (error = suser(kauth_cred_get(), 0)))
		return error;

	p = proc_find(pid);
	if (p == PROC_NULL)
		return(ESRCH);
	
	proc_lock(p);

	pcontrol = PROC_CONTROL_STATE(p);

	if(PROC_ACTION_STATE(p) !=0) {
		switch(pcontrol) {
			case P_PCTHROTTLE:
				PROC_RESETACTION_STATE(p);
				proc_unlock(p);
				printf("low swap: unthrottling pid %d (%s)\n", p->p_pid, p->p_comm);
				break;

			case P_PCSUSP:
				PROC_RESETACTION_STATE(p);
				proc_unlock(p);
				printf("low swap: resuming pid %d (%s)\n", p->p_pid, p->p_comm);
				task_resume(p->task);
				break;

			case P_PCKILL:
				/* Huh? */
				PROC_SETACTION_STATE(p);
				proc_unlock(p);
				printf("low swap: attempt to unkill pid %d (%s) ignored\n", p->p_pid, p->p_comm);
				break;

			default:
				proc_unlock(p);
		}

	} else 
		proc_unlock(p);

	proc_rele(p);
	return(0);
}