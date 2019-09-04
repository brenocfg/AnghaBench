#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_16__ ;
typedef  struct TYPE_19__   TYPE_15__ ;
typedef  struct TYPE_18__   TYPE_14__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ user_addr_t ;
typedef  scalar_t__ uint8_t ;
struct TYPE_23__ {scalar_t__ p_pid; } ;
typedef  TYPE_3__ proc_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
struct TYPE_24__ {scalar_t__ ftt_pid; scalar_t__ ftt_pc; scalar_t__ ftt_type; TYPE_6__* ftt_retids; TYPE_1__* ftt_proc; struct TYPE_24__* ftt_next; } ;
typedef  TYPE_4__ fasttrap_tracepoint_t ;
struct TYPE_25__ {scalar_t__ ftp_faddr; scalar_t__ ftp_fsize; int /*<<< orphan*/  ftp_id; int /*<<< orphan*/  ftp_triggered; TYPE_2__* ftp_prov; } ;
typedef  TYPE_5__ fasttrap_probe_t ;
struct TYPE_26__ {TYPE_5__* fti_probe; struct TYPE_26__* fti_next; } ;
typedef  TYPE_6__ fasttrap_id_t ;
struct TYPE_27__ {TYPE_4__* ftb_data; } ;
typedef  TYPE_7__ fasttrap_bucket_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_29__ {int /*<<< orphan*/ * r; } ;
struct TYPE_28__ {int /*<<< orphan*/ * x; } ;
struct TYPE_22__ {scalar_t__ ftp_provider_type; } ;
struct TYPE_21__ {scalar_t__ ftpc_acount; } ;
struct TYPE_20__ {size_t cpu_id; } ;
struct TYPE_19__ {int /*<<< orphan*/  cpuc_pid_lock; } ;
struct TYPE_18__ {int /*<<< orphan*/  p_lflag; } ;
struct TYPE_17__ {TYPE_7__* fth_table; } ;

/* Variables and functions */
 TYPE_16__* CPU ; 
 scalar_t__ DTFTP_PROVIDER_ONESHOT ; 
 int /*<<< orphan*/  DTRACEFLT_UPRIV ; 
 size_t FASTTRAP_TPOINTS_INDEX (scalar_t__,scalar_t__) ; 
 scalar_t__ FASTTRAP_T_ARM64_RET ; 
 scalar_t__ FASTTRAP_T_ARM64_RETAB ; 
 scalar_t__ FASTTRAP_T_LDM_PC ; 
 scalar_t__ FASTTRAP_T_POP_PC ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_LNOATTACH ; 
 scalar_t__ atomic_or_8 (int /*<<< orphan*/ *,int) ; 
 TYPE_15__* cpu_core ; 
 TYPE_14__* current_proc () ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_probeid_error ; 
 TYPE_12__ fasttrap_tpoints ; 
 int /*<<< orphan*/  fasttrap_tracepoint_retire (TYPE_3__*,TYPE_4__*) ; 
 scalar_t__ is_saved_state32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_9__* saved_state32 (int /*<<< orphan*/ *) ; 
 TYPE_8__* saved_state64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fasttrap_return_common(proc_t *p, arm_saved_state_t *regs, user_addr_t pc, user_addr_t new_pc)
{
	pid_t pid = p->p_pid;
	fasttrap_tracepoint_t *tp;
	fasttrap_bucket_t *bucket;
	fasttrap_id_t *id;
	lck_mtx_t *pid_mtx;
	int retire_tp = 1;
	pid_mtx = &cpu_core[CPU->cpu_id].cpuc_pid_lock;
	lck_mtx_lock(pid_mtx);
	bucket = &fasttrap_tpoints.fth_table[FASTTRAP_TPOINTS_INDEX(pid, pc)];

	for (tp = bucket->ftb_data; tp != NULL; tp = tp->ftt_next) {
		if (pid == tp->ftt_pid && pc == tp->ftt_pc &&
	    	tp->ftt_proc->ftpc_acount != 0)
			break;
	}

	/*
	 * Don't sweat it if we can't find the tracepoint again; unlike
	 * when we're in fasttrap_pid_probe(), finding the tracepoint here
	 * is not essential to the correct execution of the process.
 	 */
	if (tp == NULL) {
		lck_mtx_unlock(pid_mtx);
		return;
	}

	for (id = tp->ftt_retids; id != NULL; id = id->fti_next) {
		fasttrap_probe_t *probe = id->fti_probe;
		/*
		 * If there's a branch that could act as a return site, we
		 * need to trace it, and check here if the program counter is
		 * external to the function.
		 */
		if (is_saved_state32(regs))
		{
			if (tp->ftt_type != FASTTRAP_T_LDM_PC &&
			    tp->ftt_type != FASTTRAP_T_POP_PC &&
			    new_pc - probe->ftp_faddr < probe->ftp_fsize)
				continue;
		}
		else {
			/* ARM64_TODO  - check for FASTTRAP_T_RET */
			if ((tp->ftt_type != FASTTRAP_T_ARM64_RET || tp->ftt_type != FASTTRAP_T_ARM64_RETAB) &&
				new_pc - probe->ftp_faddr < probe->ftp_fsize)
				continue;
		}
		if (probe->ftp_prov->ftp_provider_type == DTFTP_PROVIDER_ONESHOT) {
			uint8_t already_triggered = atomic_or_8(&probe->ftp_triggered, 1);
			if (already_triggered) {
				continue;
			}
		}
		/*
		 * If we have at least one probe associated that
		 * is not a oneshot probe, don't remove the
		 * tracepoint
		 */
		else {
			retire_tp = 0;
		}

#ifndef CONFIG_EMBEDDED
		if (ISSET(current_proc()->p_lflag, P_LNOATTACH)) {
			dtrace_probe(dtrace_probeid_error, 0 /* state */, id->fti_probe->ftp_id,
				     1 /* ndx */, -1 /* offset */, DTRACEFLT_UPRIV);
#else
		if (FALSE) {
#endif
		} else {
			if (is_saved_state32(regs)) {
				dtrace_probe(probe->ftp_id,
						 pc - id->fti_probe->ftp_faddr,
				                 saved_state32(regs)->r[0], 0, 0, 0);
			} else {
				dtrace_probe(probe->ftp_id,
						 pc - id->fti_probe->ftp_faddr,
						 saved_state64(regs)->x[0], 0, 0, 0);
			}
		}
	}
	if (retire_tp) {
		fasttrap_tracepoint_retire(p, tp);
	}

	lck_mtx_unlock(pid_mtx);
}