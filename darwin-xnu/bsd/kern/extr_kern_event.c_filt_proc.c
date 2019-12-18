#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_7__ {TYPE_2__* p_proc; } ;
struct knote {int kn_sfflags; int kn_fflags; int kn_flags; long kn_data; TYPE_3__ kn_ptr; } ;
struct TYPE_8__ {TYPE_1__* kq_p; } ;
struct TYPE_6__ {scalar_t__ p_oppid; scalar_t__ p_ppid; int p_lflag; int p_csflags; } ;
struct TYPE_5__ {scalar_t__ p_pid; } ;

/* Variables and functions */
 int CS_KILLED ; 
 int EV_EOF ; 
 int EV_ONESHOT ; 
 int NOTE_EXIT ; 
 int NOTE_EXITSTATUS ; 
 long NOTE_EXIT_CSERROR ; 
 long NOTE_EXIT_DECRYPTFAIL ; 
 int NOTE_EXIT_DETAIL ; 
 long NOTE_EXIT_MEMORY ; 
 long NOTE_EXIT_MEMORY_FCTHRASHING ; 
 long NOTE_EXIT_MEMORY_HIWAT ; 
 long NOTE_EXIT_MEMORY_IDLE ; 
 long NOTE_EXIT_MEMORY_PID ; 
 long NOTE_EXIT_MEMORY_VMPAGESHORTAGE ; 
 long NOTE_EXIT_MEMORY_VMTHRASHING ; 
 long NOTE_EXIT_MEMORY_VNODE ; 
 int NOTE_PCTRLMASK ; 
 long NOTE_PDATAMASK ; 
 int NOTE_REAP ; 
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
 TYPE_4__* knote_get_kq (struct knote*) ; 

__attribute__((used)) static int
filt_proc(struct knote *kn, long hint)
{
	u_int event;

	/* ALWAYS CALLED WITH proc_klist_lock */

	/*
	 * Note: a lot of bits in hint may be obtained from the knote
	 * To free some of those bits, see <rdar://problem/12592988> Freeing up
	 * bits in hint for filt_proc
	 *
	 * mask off extra data
	 */
	event = (u_int)hint & NOTE_PCTRLMASK;

	/*
	 * termination lifecycle events can happen while a debugger
	 * has reparented a process, in which case notifications
	 * should be quashed except to the tracing parent. When
	 * the debugger reaps the child (either via wait4(2) or
	 * process exit), the child will be reparented to the original
	 * parent and these knotes re-fired.
	 */
	if (event & NOTE_EXIT) {
		if ((kn->kn_ptr.p_proc->p_oppid != 0)
		    && (knote_get_kq(kn)->kq_p->p_pid != kn->kn_ptr.p_proc->p_ppid)) {
			/*
			 * This knote is not for the current ptrace(2) parent, ignore.
			 */
			return 0;
		}
	}

	/*
	 * if the user is interested in this event, record it.
	 */
	if (kn->kn_sfflags & event)
		kn->kn_fflags |= event;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
	if ((event == NOTE_REAP) || ((event == NOTE_EXIT) && !(kn->kn_sfflags & NOTE_REAP))) {
		kn->kn_flags |= (EV_EOF | EV_ONESHOT);
	}
#pragma clang diagnostic pop


	/*
	 * The kernel has a wrapper in place that returns the same data
	 * as is collected here, in kn_data.  Any changes to how
	 * NOTE_EXITSTATUS and NOTE_EXIT_DETAIL are collected
	 * should also be reflected in the proc_pidnoteexit() wrapper.
	 */
	if (event == NOTE_EXIT) {
		kn->kn_data = 0;
		if ((kn->kn_sfflags & NOTE_EXITSTATUS) != 0) {
			kn->kn_fflags |= NOTE_EXITSTATUS;
			kn->kn_data |= (hint & NOTE_PDATAMASK);
		}
		if ((kn->kn_sfflags & NOTE_EXIT_DETAIL) != 0) {
			kn->kn_fflags |= NOTE_EXIT_DETAIL;
			if ((kn->kn_ptr.p_proc->p_lflag &
			     P_LTERM_DECRYPTFAIL) != 0) {
				kn->kn_data |= NOTE_EXIT_DECRYPTFAIL;
			}
			if ((kn->kn_ptr.p_proc->p_lflag &
			     P_LTERM_JETSAM) != 0) {
				kn->kn_data |= NOTE_EXIT_MEMORY;
				switch (kn->kn_ptr.p_proc->p_lflag & P_JETSAM_MASK) {
				case P_JETSAM_VMPAGESHORTAGE:
					kn->kn_data |= NOTE_EXIT_MEMORY_VMPAGESHORTAGE;
					break;
				case P_JETSAM_VMTHRASHING:
					kn->kn_data |= NOTE_EXIT_MEMORY_VMTHRASHING;
					break;
				case P_JETSAM_FCTHRASHING:
					kn->kn_data |= NOTE_EXIT_MEMORY_FCTHRASHING;
					break;
				case P_JETSAM_VNODE:
					kn->kn_data |= NOTE_EXIT_MEMORY_VNODE;
					break;
				case P_JETSAM_HIWAT:
					kn->kn_data |= NOTE_EXIT_MEMORY_HIWAT;
					break;
				case P_JETSAM_PID:
					kn->kn_data |= NOTE_EXIT_MEMORY_PID;
					break;
				case P_JETSAM_IDLEEXIT:
					kn->kn_data |= NOTE_EXIT_MEMORY_IDLE;
					break;
				}
			}
			if ((kn->kn_ptr.p_proc->p_csflags &
			     CS_KILLED) != 0) {
				kn->kn_data |= NOTE_EXIT_CSERROR;
			}
		}
	}

	/* if we have any matching state, activate the knote */
	return (kn->kn_fflags != 0);
}