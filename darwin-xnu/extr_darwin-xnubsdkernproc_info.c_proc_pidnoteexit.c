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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ pid_t ;
struct TYPE_5__ {scalar_t__ p_ppid; int p_lflag; scalar_t__ p_oppid; int p_xstat; int p_csflags; } ;

/* Variables and functions */
 int CS_KILLED ; 
 int EACCES ; 
 int NOTE_EXITSTATUS ; 
 int NOTE_EXIT_CSERROR ; 
 int NOTE_EXIT_DECRYPTFAIL ; 
 int NOTE_EXIT_DETAIL ; 
 int NOTE_EXIT_MEMORY ; 
 int NOTE_EXIT_MEMORY_FCTHRASHING ; 
 int NOTE_EXIT_MEMORY_HIWAT ; 
 int NOTE_EXIT_MEMORY_IDLE ; 
 int NOTE_EXIT_MEMORY_PID ; 
 int NOTE_EXIT_MEMORY_VMPAGESHORTAGE ; 
 int NOTE_EXIT_MEMORY_VMTHRASHING ; 
 int NOTE_EXIT_MEMORY_VNODE ; 
 int NOTE_PDATAMASK ; 
#define  P_JETSAM_FCTHRASHING 134 
#define  P_JETSAM_HIWAT 133 
#define  P_JETSAM_IDLEEXIT 132 
 int P_JETSAM_MASK ; 
#define  P_JETSAM_PID 131 
#define  P_JETSAM_VMPAGESHORTAGE 130 
#define  P_JETSAM_VMTHRASHING 129 
#define  P_JETSAM_VNODE 128 
 int P_LTERM_DECRYPTFAIL ; 
 int P_LTERM_JETSAM ; 
 int P_LTRACED ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 scalar_t__ proc_selfpid () ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 

int
proc_pidnoteexit(proc_t p, uint64_t flags, uint32_t *data)
{
	uint32_t exit_data = 0;
	uint32_t exit_flags = (uint32_t)flags;

	proc_lock(p);

	/*
	 * Allow access to the parent of the exiting
	 * child or the parent debugger only.
	 */
	do {
		pid_t selfpid = proc_selfpid();

		if (p->p_ppid == selfpid)
			break;  /* parent => ok */
	
		if ((p->p_lflag & P_LTRACED) != 0 &&
		    (p->p_oppid == selfpid))
			break;  /* parent-in-waiting => ok */

		proc_unlock(p);
		return (EACCES);
	} while (0);
	
	if ((exit_flags & NOTE_EXITSTATUS) != 0) {
		/* The signal and exit status */
		exit_data |= (p->p_xstat & NOTE_PDATAMASK);
	}

	if ((exit_flags & NOTE_EXIT_DETAIL) != 0) {
		/* The exit detail */
		if ((p->p_lflag & P_LTERM_DECRYPTFAIL) != 0) {
			exit_data |= NOTE_EXIT_DECRYPTFAIL;
		}

		if ((p->p_lflag & P_LTERM_JETSAM) != 0) {
			exit_data |= NOTE_EXIT_MEMORY;

			switch (p->p_lflag & P_JETSAM_MASK) {
			case P_JETSAM_VMPAGESHORTAGE:
				exit_data |= NOTE_EXIT_MEMORY_VMPAGESHORTAGE;
				break;
			case P_JETSAM_VMTHRASHING:
				exit_data |= NOTE_EXIT_MEMORY_VMTHRASHING;
				break;
			case P_JETSAM_FCTHRASHING:
				exit_data |= NOTE_EXIT_MEMORY_FCTHRASHING;
				break;
			case P_JETSAM_VNODE:
				exit_data |= NOTE_EXIT_MEMORY_VNODE;
				break;
			case P_JETSAM_HIWAT:
				exit_data |= NOTE_EXIT_MEMORY_HIWAT;
				break;
			case P_JETSAM_PID:
				exit_data |= NOTE_EXIT_MEMORY_PID;
				break;
			case P_JETSAM_IDLEEXIT:
				exit_data |= NOTE_EXIT_MEMORY_IDLE;
				break;
			}
		}

		if ((p->p_csflags & CS_KILLED) != 0) {
			exit_data |= NOTE_EXIT_CSERROR;
		}
	}

	proc_unlock(p);

	*data = exit_data;

	return (0);
}