#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_28__ ;
typedef  struct TYPE_31__   TYPE_27__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_15__ ;

/* Type definitions */
typedef  TYPE_3__* uthread_t ;
typedef  scalar_t__ user_addr_t ;
typedef  int uint_t ;
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_35__ {int p_lflag; scalar_t__ p_pid; struct TYPE_35__* p_pptr; } ;
typedef  TYPE_4__ proc_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
struct TYPE_36__ {scalar_t__ ftt_pid; scalar_t__ ftt_pc; int /*<<< orphan*/ * ftt_retids; TYPE_7__* ftt_ids; scalar_t__ ftt_thumb; TYPE_1__* ftt_proc; struct TYPE_36__* ftt_next; } ;
typedef  TYPE_5__ fasttrap_tracepoint_t ;
struct TYPE_37__ {scalar_t__ ftp_id; int /*<<< orphan*/ * ftp_argmap; int /*<<< orphan*/  ftp_triggered; TYPE_2__* ftp_prov; } ;
typedef  TYPE_6__ fasttrap_probe_t ;
struct TYPE_38__ {scalar_t__ fti_ptype; TYPE_6__* fti_probe; struct TYPE_38__* fti_next; } ;
typedef  TYPE_7__ fasttrap_id_t ;
struct TYPE_39__ {TYPE_5__* ftb_data; } ;
typedef  TYPE_8__ fasttrap_bucket_t ;
typedef  int /*<<< orphan*/  dtrace_icookie_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_34__ {int t_dtrace_on; scalar_t__ t_dtrace_pc; scalar_t__ t_dtrace_scrpc; scalar_t__ t_dtrace_astpc; scalar_t__ t_dtrace_ret; scalar_t__ t_dtrace_reg; scalar_t__ t_dtrace_npc; scalar_t__ t_dtrace_ft; scalar_t__ t_dtrace_step; } ;
struct TYPE_33__ {scalar_t__ ftp_provider_type; } ;
struct TYPE_32__ {size_t cpu_id; } ;
struct TYPE_31__ {int /*<<< orphan*/  cpuc_pid_lock; } ;
struct TYPE_30__ {scalar_t__ ftpc_acount; } ;
struct TYPE_29__ {TYPE_8__* fth_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_28__* CPU ; 
 int /*<<< orphan*/  CPU_DTRACE_ENTRY ; 
 scalar_t__ DTFTP_ENTRY ; 
 scalar_t__ DTFTP_IS_ENABLED ; 
 scalar_t__ DTFTP_PROVIDER_ONESHOT ; 
 scalar_t__ DTRACEFLT_UPRIV ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 size_t FASTTRAP_TPOINTS_INDEX (scalar_t__,scalar_t__) ; 
 scalar_t__ ISSET (int,int /*<<< orphan*/ ) ; 
 int P_LINVFORK ; 
 int /*<<< orphan*/  P_LNOATTACH ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ atomic_or_8 (int /*<<< orphan*/ *,int) ; 
 TYPE_27__* cpu_core ; 
 TYPE_4__* current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  dtrace_interrupt_disable () ; 
 int /*<<< orphan*/  dtrace_interrupt_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_probe (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ dtrace_probeid_error ; 
 int /*<<< orphan*/  fasttrap_fuword32_noerr (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  fasttrap_pid_probe_handle_patched_instr32 (int /*<<< orphan*/ *,TYPE_5__*,TYPE_3__*,TYPE_4__*,int,int*) ; 
 int /*<<< orphan*/  fasttrap_pid_probe_handle_patched_instr64 (int /*<<< orphan*/ *,TYPE_5__*,TYPE_3__*,TYPE_4__*,int,int*) ; 
 int /*<<< orphan*/  fasttrap_pid_probe_thumb_state_valid (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  fasttrap_return_common (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fasttrap_sigtrap (TYPE_4__*,TYPE_3__*,scalar_t__) ; 
 TYPE_15__ fasttrap_tpoints ; 
 int /*<<< orphan*/  fasttrap_tracepoint_remove (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  fasttrap_tracepoint_retire (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  fasttrap_usdt_args32 (TYPE_6__*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  fasttrap_usdt_args64 (TYPE_6__*,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 scalar_t__ get_saved_state_pc (int /*<<< orphan*/ *) ; 
 scalar_t__ get_saved_state_reg (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_saved_state_sp (int /*<<< orphan*/ *) ; 
 int is_saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  saved_state32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saved_state64 (int /*<<< orphan*/ *) ; 

int
fasttrap_pid_probe(arm_saved_state_t *state)
{
	proc_t *p = current_proc();
	fasttrap_bucket_t *bucket;
	lck_mtx_t *pid_mtx;
	fasttrap_tracepoint_t *tp, tp_local;
	pid_t pid;
	dtrace_icookie_t cookie;
	uint_t is_enabled = 0;
	int was_simulated, retire_tp = 1;
	int is_64_bit = is_saved_state64(state);

	uint64_t pc = get_saved_state_pc(state);

	assert(is_64_bit || (pc <= UINT32_MAX));

	uthread_t uthread = (uthread_t) get_bsdthread_info(current_thread());

	/*
	 * It's possible that a user (in a veritable orgy of bad planning)
	 * could redirect this thread's flow of control before it reached the
	 * return probe fasttrap. In this case we need to kill the process
	 * since it's in a unrecoverable state.
	 */
	if (uthread->t_dtrace_step) {
		ASSERT(uthread->t_dtrace_on);
		fasttrap_sigtrap(p, uthread, (user_addr_t)pc);
		return (0);
	}

	/*
	 * Clear all user tracing flags.
	 */
	uthread->t_dtrace_ft = 0;
	uthread->t_dtrace_pc = 0;
	uthread->t_dtrace_npc = 0;
	uthread->t_dtrace_scrpc = 0;
	uthread->t_dtrace_astpc = 0;
	uthread->t_dtrace_reg = 0;

	/*
	 * Treat a child created by a call to vfork(2) as if it were its
	 * parent. We know that there's only one thread of control in such a
	 * process: this one.
	 */
	if (p->p_lflag & P_LINVFORK) {
		proc_list_lock();
		while (p->p_lflag & P_LINVFORK)
			p = p->p_pptr;
		proc_list_unlock();
	}

	pid = p->p_pid;
	pid_mtx = &cpu_core[CPU->cpu_id].cpuc_pid_lock;
	lck_mtx_lock(pid_mtx);
	bucket = &fasttrap_tpoints.fth_table[FASTTRAP_TPOINTS_INDEX(pid,pc)];

	/*
	 * Lookup the tracepoint that the process just hit.
	 */
	for (tp = bucket->ftb_data; tp != NULL; tp = tp->ftt_next) {
		if (pid == tp->ftt_pid && pc == tp->ftt_pc &&
		    tp->ftt_proc->ftpc_acount != 0)
			break;
	}

	/*
	 * If we couldn't find a matching tracepoint, either a tracepoint has
	 * been inserted without using the pid<pid> ioctl interface (see
	 * fasttrap_ioctl), or somehow we have mislaid this tracepoint.
	 */
	if (tp == NULL) {
		lck_mtx_unlock(pid_mtx);
		return (-1);
	}

	/* Validation of THUMB-related state */
	if (tp->ftt_thumb) {
		if (!fasttrap_pid_probe_thumb_state_valid(saved_state32(state), tp)) {
			fasttrap_tracepoint_remove(p, tp);
			lck_mtx_unlock(pid_mtx);
			return (-1);
		}
	}

	/* Execute the actual probe */
	if (tp->ftt_ids != NULL) {
		fasttrap_id_t *id;
		uint64_t arg4;

		if (is_saved_state64(state)) {
			arg4 = get_saved_state_reg(state, 4);
		} else {
			uint32_t arg;
			user_addr_t stack = (user_addr_t)get_saved_state_sp(state);

			fasttrap_fuword32_noerr(stack, &arg);
			arg4 = arg;
		}


		/* First four parameters are passed in registers */

		for (id = tp->ftt_ids; id != NULL; id = id->fti_next) {
			fasttrap_probe_t *probe = id->fti_probe;

#ifndef CONFIG_EMBEDDED
			if (ISSET(current_proc()->p_lflag, P_LNOATTACH)) {
				dtrace_probe(dtrace_probeid_error, 0 /* state */, probe->ftp_id,
					     1 /* ndx */, -1 /* offset */, DTRACEFLT_UPRIV);
#else
			if (FALSE) {
#endif
			} else {
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
				if (id->fti_ptype == DTFTP_ENTRY) {
					/*
					 * We note that this was an entry
					 * probe to help ustack() find the
					 * first caller.
					 */
					cookie = dtrace_interrupt_disable();
					DTRACE_CPUFLAG_SET(CPU_DTRACE_ENTRY);
					dtrace_probe(probe->ftp_id,
							get_saved_state_reg(state, 0),
							get_saved_state_reg(state, 1),
							get_saved_state_reg(state, 2),
							get_saved_state_reg(state, 3),
							arg4);
					DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_ENTRY);
					dtrace_interrupt_enable(cookie);
				} else if (id->fti_ptype == DTFTP_IS_ENABLED) {
					/*
					 * Note that in this case, we don't
					 * call dtrace_probe() since it's only
					 * an artificial probe meant to change
					 * the flow of control so that it
					 * encounters the true probe.
					 */
					is_enabled = 1;
				} else if (probe->ftp_argmap == NULL) {
					dtrace_probe(probe->ftp_id,
							get_saved_state_reg(state, 0),
							get_saved_state_reg(state, 1),
							get_saved_state_reg(state, 2),
							get_saved_state_reg(state, 3),
							arg4);

				} else {
					uint64_t t[5];

					if (is_64_bit) {
						fasttrap_usdt_args64(probe, saved_state64(state), 5, t);
					} else {
						fasttrap_usdt_args32(probe, saved_state32(state), 5, t);
					}
					dtrace_probe(probe->ftp_id, t[0], t[1], t[2], t[3], t[4]);
				}
			}
		}
		if (retire_tp) {
			fasttrap_tracepoint_retire(p, tp);
		}
	}
	/*
	 * We're about to do a bunch of work so we cache a local copy of
	 * the tracepoint to emulate the instruction, and then find the
	 * tracepoint again later if we need to light up any return probes.
	 */
	tp_local = *tp;
	lck_mtx_unlock(pid_mtx);
	tp = &tp_local;

	/*
	 * APPLE NOTE:
	 *
	 * Subroutines should update PC.
	 * We're setting this earlier than Solaris does, to get a "correct"
	 * ustack() output. In the Sun code,  a() -> b() -> c() -> d() is
	 * reported at: d, b, a. The new way gives c, b, a, which is closer
	 * to correct, as the return instruction has already exectued.
	 */
	if (is_64_bit) {
		fasttrap_pid_probe_handle_patched_instr64(state, tp, uthread, p, is_enabled, &was_simulated);
	} else {
		fasttrap_pid_probe_handle_patched_instr32(state, tp, uthread, p, is_enabled, &was_simulated);
	}

	/*                      
	 * If there were no return probes when we first found the tracepoint,
	 * we should feel no obligation to honor any return probes that were
	 * subsequently enabled -- they'll just have to wait until the next
	 * time around. 
	 */                     
	if (tp->ftt_retids != NULL) {
		/*
		 * We need to wait until the results of the instruction are
		 * apparent before invoking any return probes. If this
		 * instruction was emulated we can just call
		 * fasttrap_return_common(); if it needs to be executed, we
		 * need to wait until the user thread returns to the kernel.
		 */
		/*
		 * It used to be that only common instructions were simulated.
		 * For performance reasons, we now simulate some instructions
		 * when safe and go back to userland otherwise. The was_simulated
		 * flag means we don't need to go back to userland.
		 */
		if (was_simulated) {
			fasttrap_return_common(p, state, (user_addr_t)pc, (user_addr_t)get_saved_state_pc(state));
		} else {
			ASSERT(uthread->t_dtrace_ret != 0);
			ASSERT(uthread->t_dtrace_pc == pc);
			ASSERT(uthread->t_dtrace_scrpc != 0);
			ASSERT(((user_addr_t)get_saved_state_pc(state)) == uthread->t_dtrace_astpc);
		}
	}

	return (0);
}