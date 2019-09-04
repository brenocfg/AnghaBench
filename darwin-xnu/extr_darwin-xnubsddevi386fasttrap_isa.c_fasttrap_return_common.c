#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_saved_state_t ;
struct TYPE_21__ {int rdx; int /*<<< orphan*/  rax; } ;
typedef  TYPE_3__ x86_saved_state64_t ;
struct TYPE_22__ {int edx; int /*<<< orphan*/  eax; } ;
typedef  TYPE_4__ x86_saved_state32_t ;
typedef  scalar_t__ user_addr_t ;
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
struct TYPE_23__ {scalar_t__ ftt_pid; scalar_t__ ftt_pc; scalar_t__ ftt_type; TYPE_7__* ftt_retids; TYPE_1__* ftt_proc; struct TYPE_23__* ftt_next; } ;
typedef  TYPE_5__ fasttrap_tracepoint_t ;
struct TYPE_24__ {scalar_t__ ftp_faddr; scalar_t__ ftp_fsize; int /*<<< orphan*/  ftp_id; int /*<<< orphan*/  ftp_triggered; TYPE_2__* ftp_prov; } ;
typedef  TYPE_6__ fasttrap_probe_t ;
struct TYPE_25__ {TYPE_6__* fti_probe; struct TYPE_25__* fti_next; } ;
typedef  TYPE_7__ fasttrap_id_t ;
struct TYPE_26__ {TYPE_5__* ftb_data; } ;
typedef  TYPE_8__ fasttrap_bucket_t ;
typedef  int /*<<< orphan*/  dtrace_icookie_t ;
struct TYPE_20__ {scalar_t__ ftp_provider_type; } ;
struct TYPE_19__ {scalar_t__ ftpc_acount; } ;
struct TYPE_18__ {size_t cpu_id; } ;
struct TYPE_17__ {scalar_t__ cpuc_missing_tos; int /*<<< orphan*/  cpuc_pid_lock; } ;
struct TYPE_16__ {int /*<<< orphan*/  p_lflag; } ;
struct TYPE_15__ {TYPE_8__* fth_table; } ;

/* Variables and functions */
 TYPE_14__* CPU ; 
 unsigned int DATAMODEL_ILP32 ; 
 unsigned int DATAMODEL_LP64 ; 
 scalar_t__ DTFTP_PROVIDER_ONESHOT ; 
 int /*<<< orphan*/  DTRACEFLT_UPRIV ; 
 size_t FASTTRAP_TPOINTS_INDEX (scalar_t__,scalar_t__) ; 
 scalar_t__ FASTTRAP_T_RET ; 
 scalar_t__ FASTTRAP_T_RET16 ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_LNOATTACH ; 
 scalar_t__ atomic_or_8 (int /*<<< orphan*/ *,int) ; 
 TYPE_13__* cpu_core ; 
 TYPE_12__* current_proc () ; 
 int /*<<< orphan*/  dtrace_interrupt_disable () ; 
 int /*<<< orphan*/  dtrace_interrupt_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_probeid_error ; 
 TYPE_11__ fasttrap_tpoints ; 
 scalar_t__ is_saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_4__* saved_state32 (int /*<<< orphan*/ *) ; 
 TYPE_3__* saved_state64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fasttrap_return_common(x86_saved_state_t *regs, user_addr_t pc, pid_t pid,
    user_addr_t new_pc)
{
	x86_saved_state64_t *regs64;
	x86_saved_state32_t *regs32;
	unsigned int p_model;
	int retire_tp = 1;

	dtrace_icookie_t cookie;

        if (is_saved_state64(regs)) {
                regs64 = saved_state64(regs);
		regs32 = NULL;
		p_model = DATAMODEL_LP64;
        } else {
		regs64 = NULL;
                regs32 = saved_state32(regs);
		p_model = DATAMODEL_ILP32;
        }

	fasttrap_tracepoint_t *tp;
	fasttrap_bucket_t *bucket;
	fasttrap_id_t *id;
	lck_mtx_t *pid_mtx;

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
		if (tp->ftt_type != FASTTRAP_T_RET &&
		    tp->ftt_type != FASTTRAP_T_RET16 &&
		    new_pc - probe->ftp_faddr < probe->ftp_fsize)
			continue;

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
		/*
		 * Provide a hint to the stack trace functions to add the
		 * following pc to the top of the stack since it's missing
		 * on a return probe yet highly desirable for consistency.
		 */
		cookie = dtrace_interrupt_disable();
		cpu_core[CPU->cpu_id].cpuc_missing_tos = pc;
		if (ISSET(current_proc()->p_lflag, P_LNOATTACH)) {
			dtrace_probe(dtrace_probeid_error, 0 /* state */, probe->ftp_id,
				     1 /* ndx */, -1 /* offset */, DTRACEFLT_UPRIV);
		} else if (p_model == DATAMODEL_LP64) {
			dtrace_probe(probe->ftp_id,
				     pc - id->fti_probe->ftp_faddr,
				     regs64->rax, regs64->rdx, 0, 0);
		} else {
			dtrace_probe(probe->ftp_id,
				     pc - id->fti_probe->ftp_faddr,
				     regs32->eax, regs32->edx, 0, 0);
		}
		/* remove the hint */
		cpu_core[CPU->cpu_id].cpuc_missing_tos = 0;
		dtrace_interrupt_enable(cookie);
	}

	lck_mtx_unlock(pid_mtx);
}