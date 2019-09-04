#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
struct TYPE_9__ {int p_pid; char* p_comm; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 scalar_t__ PROC_ACTION_STATE (TYPE_1__*) ; 
 int PROC_CONTROL_STATE (TYPE_1__*) ; 
 int PROC_RETURNED ; 
 int /*<<< orphan*/  PROC_SETACTION_STATE (TYPE_1__*) ; 
#define  P_PCKILL 130 
#define  P_PCSUSP 129 
#define  P_PCTHROTTLE 128 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  psignal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_suspend (int /*<<< orphan*/ ) ; 

int
proc_dopcontrol(proc_t p)
{
	int pcontrol;

	proc_lock(p);

	pcontrol = PROC_CONTROL_STATE(p);

	if (PROC_ACTION_STATE(p) == 0) {
		switch(pcontrol) {
			case P_PCTHROTTLE:
				PROC_SETACTION_STATE(p);
				proc_unlock(p);
				printf("low swap: throttling pid %d (%s)\n", p->p_pid, p->p_comm);
				break;

			case P_PCSUSP:
				PROC_SETACTION_STATE(p);
				proc_unlock(p);
				printf("low swap: suspending pid %d (%s)\n", p->p_pid, p->p_comm);
				task_suspend(p->task);
				break;

			case P_PCKILL:
				PROC_SETACTION_STATE(p);
				proc_unlock(p);
				printf("low swap: killing pid %d (%s)\n", p->p_pid, p->p_comm);
				psignal(p, SIGKILL);
				break;

			default:
				proc_unlock(p);
		}

	} else 
		proc_unlock(p);

	return(PROC_RETURNED);
}