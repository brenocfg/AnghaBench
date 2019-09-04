#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_9__ ;
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_33__ ;
typedef  struct TYPE_40__   TYPE_31__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_21__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_12__ ;
typedef  struct TYPE_35__   TYPE_11__ ;
typedef  struct TYPE_34__   TYPE_10__ ;

/* Type definitions */
typedef  TYPE_5__* uthread_t ;
typedef  scalar_t__ user_addr_t ;
typedef  int uint_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_45__ {int p_lflag; scalar_t__ p_pid; struct TYPE_45__* p_pptr; } ;
typedef  TYPE_6__ proc_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
struct TYPE_46__ {scalar_t__ ftt_pid; scalar_t__ ftt_pc; int ftt_thumb; int ftt_instr; int ftt_instr1; int ftt_type; int ftt_instr2; int /*<<< orphan*/ * ftt_retids; TYPE_10__* ftt_ids; TYPE_1__* ftt_proc; struct TYPE_46__* ftt_next; } ;
typedef  TYPE_7__ fasttrap_tracepoint_t ;
struct TYPE_47__ {int ftp_id; int /*<<< orphan*/ * ftp_argmap; int /*<<< orphan*/  ftp_triggered; TYPE_2__* ftp_prov; } ;
typedef  TYPE_8__ fasttrap_probe_t ;
struct TYPE_42__ {int instr1; } ;
struct TYPE_48__ {int instr32; TYPE_3__ instr16; } ;
typedef  TYPE_9__ fasttrap_instr_t ;
struct TYPE_34__ {scalar_t__ fti_ptype; TYPE_8__* fti_probe; struct TYPE_34__* fti_next; } ;
typedef  TYPE_10__ fasttrap_id_t ;
struct TYPE_35__ {TYPE_7__* ftb_data; } ;
typedef  TYPE_11__ fasttrap_bucket_t ;
typedef  int /*<<< orphan*/  dtrace_icookie_t ;
struct TYPE_36__ {scalar_t__ pc; int cpsr; uintptr_t sp; int* r; scalar_t__ lr; } ;
typedef  TYPE_12__ arm_saved_state_t ;
struct TYPE_44__ {int t_dtrace_step; int t_dtrace_on; scalar_t__ t_dtrace_pc; scalar_t__ t_dtrace_scrpc; scalar_t__ t_dtrace_astpc; int t_dtrace_ret; scalar_t__ t_dtrace_npc; TYPE_4__* t_dtrace_scratch; scalar_t__ t_dtrace_ft; } ;
struct TYPE_43__ {scalar_t__ addr; int /*<<< orphan*/  write_addr; } ;
struct TYPE_41__ {size_t cpu_id; } ;
struct TYPE_40__ {int /*<<< orphan*/  cpuc_pid_lock; } ;
struct TYPE_39__ {scalar_t__ ftp_provider_type; } ;
struct TYPE_38__ {TYPE_11__* fth_table; } ;
struct TYPE_37__ {scalar_t__ ftpc_acount; } ;

/* Variables and functions */
 void* ALIGNADDR (scalar_t__,int) ; 
 int ARM_CONDCODE (int) ; 
 int ARM_RM (int) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_33__* CPU ; 
 int /*<<< orphan*/  CPU_DTRACE_ENTRY ; 
 scalar_t__ DTFTP_ENTRY ; 
 scalar_t__ DTFTP_IS_ENABLED ; 
 scalar_t__ DTFTP_PROVIDER_ONESHOT ; 
 int DTRACEFLT_UPRIV ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 int FASTTRAP_ARM_RET_INSTR ; 
 int FASTTRAP_THUMB_RET_INSTR ; 
 size_t FASTTRAP_TPOINTS_INDEX (scalar_t__,scalar_t__) ; 
#define  FASTTRAP_T_BX_REG 140 
#define  FASTTRAP_T_B_COND 139 
#define  FASTTRAP_T_B_UNCOND 138 
#define  FASTTRAP_T_CB_N_Z 137 
#define  FASTTRAP_T_COMMON 136 
#define  FASTTRAP_T_CPY_PC 135 
#define  FASTTRAP_T_LDM_PC 134 
#define  FASTTRAP_T_LDR_PC_IMMED 133 
#define  FASTTRAP_T_MOV_PC_REG 132 
#define  FASTTRAP_T_POP_PC 131 
#define  FASTTRAP_T_PUSH_LR 130 
#define  FASTTRAP_T_STM_LR 129 
#define  FASTTRAP_T_VLDR_PC_IMMED 128 
 int GETITSTATE (int) ; 
 scalar_t__ ISLASTINIT (int) ; 
 scalar_t__ ISSET (int,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ARM_NOP (int) ; 
 scalar_t__ IS_THUMB_NOP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 uintptr_t PAGE_SHIFT ; 
 int PSR_TF ; 
 int P_LINVFORK ; 
 int /*<<< orphan*/  P_LNOATTACH ; 
 int /*<<< orphan*/  SET16 (int*,int) ; 
 int /*<<< orphan*/  SET32 (int*,int) ; 
 int SIGNEXTEND (int,int) ; 
 int THUMB16_HRM (int) ; 
 int /*<<< orphan*/  THUMB_INSTR (int) ; 
 int atomic_or_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcopy (TYPE_9__*,int*,int) ; 
 TYPE_31__* cpu_core ; 
 TYPE_6__* current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  dtrace_arm_condition_true (int,int) ; 
 int dtrace_instr_size (int,int) ; 
 int /*<<< orphan*/  dtrace_interrupt_disable () ; 
 int /*<<< orphan*/  dtrace_interrupt_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_probe (int,int,int,int,int,int) ; 
 int dtrace_probeid_error ; 
 int fasttrap_fuword32 (int,scalar_t__*) ; 
 int /*<<< orphan*/  fasttrap_fuword32_noerr (scalar_t__,int*) ; 
 int /*<<< orphan*/  fasttrap_return_common (TYPE_6__*,TYPE_12__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fasttrap_sigsegv (TYPE_6__*,TYPE_5__*,scalar_t__,TYPE_12__*) ; 
 int /*<<< orphan*/  fasttrap_sigtrap (TYPE_6__*,TYPE_5__*,scalar_t__) ; 
 int fasttrap_suword32 (int,scalar_t__) ; 
 TYPE_21__ fasttrap_tpoints ; 
 int /*<<< orphan*/  fasttrap_tracepoint_remove (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  fasttrap_tracepoint_retire (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  fasttrap_usdt_args (TYPE_8__*,TYPE_12__*,int,int*) ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 int /*<<< orphan*/  set_thumb_flag (TYPE_12__*,scalar_t__) ; 
 int /*<<< orphan*/  uwrite (TYPE_6__*,int*,int,int /*<<< orphan*/ ) ; 

int
fasttrap_pid_probe(arm_saved_state_t *regs)
{
	proc_t *p = current_proc();
	user_addr_t new_pc = 0;
	fasttrap_bucket_t *bucket;
	lck_mtx_t *pid_mtx;
	fasttrap_tracepoint_t *tp, tp_local;
	pid_t pid;
	dtrace_icookie_t cookie;
	uint_t is_enabled = 0;
	int instr_size;
	int was_simulated = 1, retire_tp = 1;

	user_addr_t pc = regs->pc;

	uthread_t uthread = (uthread_t) get_bsdthread_info(current_thread());

	/*
	 * It's possible that a user (in a veritable orgy of bad planning)
	 * could redirect this thread's flow of control before it reached the
	 * return probe fasttrap. In this case we need to kill the process
	 * since it's in a unrecoverable state.
	 */
	if (uthread->t_dtrace_step) {
		ASSERT(uthread->t_dtrace_on);
		fasttrap_sigtrap(p, uthread, pc);
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

	/* Default to always execute */
	int condition_code = 0xE;
	if (tp->ftt_thumb) {
		uint32_t itstate = GETITSTATE(regs->cpsr);
		if (itstate != 0) {
			/* In IT block, make sure it's the last statement in the block */
			if (ISLASTINIT(itstate)) {
				condition_code = itstate >> 4;
			} else {
				printf("dtrace: fasttrap: Tried to trace instruction %08x at %08x but not at end of IT block\n",
				    (tp->ftt_thumb && dtrace_instr_size(tp->ftt_instr,tp->ftt_thumb) == 2) ? tp->ftt_instr1 : tp->ftt_instr, pc);

				fasttrap_tracepoint_remove(p, tp);
				lck_mtx_unlock(pid_mtx);
				return (-1);
			}
		}
	} else {
		condition_code = ARM_CONDCODE(tp->ftt_instr);
	}

	if (!tp->ftt_thumb != !(regs->cpsr & PSR_TF)) {
		/* The ARM/Thumb mode does not match what we expected for this probe.
		 * Remove this probe and bail.
		 */
		fasttrap_tracepoint_remove(p, tp);
		lck_mtx_unlock(pid_mtx);
		return (-1);
	}

	if (tp->ftt_ids != NULL) {
		fasttrap_id_t *id;

		uint32_t s4;
		uint32_t *stack = (uint32_t *)regs->sp;

		/* First four parameters are passed in registers */
		fasttrap_fuword32_noerr((user_addr_t)(uint32_t)stack, &s4);

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
				 * If we have at least probe associated that
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
					dtrace_probe(probe->ftp_id, regs->r[0], regs->r[1], regs->r[2], regs->r[3], s4);
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
					dtrace_probe(probe->ftp_id, regs->r[0], regs->r[1], regs->r[2], regs->r[3], s4);
				} else {
					uint32_t t[5];

					fasttrap_usdt_args(probe, regs, 5, t);
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
	 * If there's an is-enabled probe connected to this tracepoint it
	 * means that there was a 'eor r0,r0,r0'
	 * instruction that was placed there by DTrace when the binary was
	 * linked. As this probe is, in fact, enabled, we need to stuff 1
	 * into R0. Accordingly, we can bypass all the instruction
	 * emulation logic since we know the inevitable result. It's possible
	 * that a user could construct a scenario where the 'is-enabled'
	 * probe was on some other instruction, but that would be a rather
	 * exotic way to shoot oneself in the foot.
	 */

	if (is_enabled) {
		regs->r[0] = 1;
		new_pc = regs->pc + (tp->ftt_thumb ? 2 : 4);
		goto done;
	}

	/* For USDT probes, bypass all the emulation logic for the nop instruction */
	if ((tp->ftt_thumb && IS_THUMB_NOP(THUMB_INSTR(tp->ftt_instr))) ||
	    (!tp->ftt_thumb && IS_ARM_NOP(tp->ftt_instr))) {
		new_pc = regs->pc + (tp->ftt_thumb ? 2 : 4);
		goto done;
	}

	instr_size = dtrace_instr_size(tp->ftt_instr,tp->ftt_thumb);

	switch (tp->ftt_type) {
		case FASTTRAP_T_MOV_PC_REG:
		case FASTTRAP_T_CPY_PC:
		{
			if (!dtrace_arm_condition_true(condition_code, regs->cpsr)) {
				new_pc = pc + instr_size;
				break;
			}

			int rm;
			if (tp->ftt_thumb) {
				rm = THUMB16_HRM(tp->ftt_instr1);
			} else {
				rm = tp->ftt_instr & 0xF;
			}
			new_pc = regs->r[rm];

			/* This instruction does not change the Thumb state */

			break;
		}

		case FASTTRAP_T_STM_LR:
		case FASTTRAP_T_PUSH_LR:
		{
			/*
			 * This is a very common case, so we want to emulate this instruction if
			 * possible. However, on a push, it is possible that we might reach the end
			 * of a page and have to allocate a new page. Most of the time this will not
			 * happen, and we know that the push instruction can store at most 16 words,
			 * so check to see if we are far from the boundary, and if so, emulate. This
			 * can be made more aggressive by checking the actual number of words being
			 * pushed, but we won't do that for now.
			 *
			 * Some of the same issues that apply to POP_PC probably apply here also.
			 */

			int reglist;
			int ret;
			uintptr_t* base;

			if (!dtrace_arm_condition_true(condition_code, regs->cpsr)) {
				new_pc = pc + instr_size;
				break;
			}

			base = (uintptr_t*) regs->sp;
			if (((((uintptr_t) base)-16*4) >> PAGE_SHIFT) != (((uintptr_t) base) >> PAGE_SHIFT)) {
				/* Crosses the page boundary, go to emulation */
				goto instr_emulate;
			}

			if (tp->ftt_thumb) {
				if (instr_size == 4) {
					/* We know we have to push lr, never push sp or pc */
					reglist = tp->ftt_instr2 & 0x1FFF;
				} else {
					reglist = tp->ftt_instr1 & 0xFF;
				}
			} else {
				/* We know we have to push lr, never push sp or pc */
				reglist = tp->ftt_instr & 0x1FFF;
			}

			/* Push the link register */
			base--;
			ret = fasttrap_suword32((uint32_t) base, regs->lr);
			if (ret == -1) {
				fasttrap_sigsegv(p, uthread, (user_addr_t) base, regs);
				new_pc = regs->pc;
				break;
			}

			/* Start pushing from $r12 */
			int regmask = 1 << 12;
			int regnum = 12;

			while (regmask) {
				if (reglist & regmask) {
					base--;
					ret = fasttrap_suword32((uint32_t) base, regs->r[regnum]);
					if (ret == -1) {
						fasttrap_sigsegv(p, uthread, (user_addr_t) base, regs);
						new_pc = regs->pc;
						break;
					}
				}
				regmask >>= 1;
				regnum--;
			}

			regs->sp = (uintptr_t) base;

			new_pc = pc + instr_size;

			break;
		}


		case FASTTRAP_T_LDM_PC:
		case FASTTRAP_T_POP_PC:
		{
			/* TODO Two issues that will eventually need to be resolved:
			 *
			 * 1. Understand what the hardware does if we have to segfault (data abort) in
			 * the middle of a load multiple. We currently don't have a working segfault
			 * handler anyway, and with no swapfile we should never segfault on this load.
			 * If we do, we'll just kill the process by setting the pc to 0.
			 *
			 * 2. The emulation is no longer atomic. We currently only emulate pop for
			 * function epilogues, and so we should never have a race here because one
			 * thread should never be trying to manipulate another thread's stack frames.
			 * That is almost certainly a bug in the program.
			 * 
			 * This will need to be fixed if we ever:
			 *   a. Ship dtrace externally, as this could be a potential attack vector
			 *   b. Support instruction level tracing, as we might then pop/ldm non epilogues.
			 *
			 */

			/* Assume ldmia! sp/pop ... pc */

			int regnum = 0, reglist;
			int ret;
			uintptr_t* base;

			if (!dtrace_arm_condition_true(condition_code, regs->cpsr)) {
				new_pc = pc + instr_size;
				break;
			}

			if (tp->ftt_thumb) {
				if (instr_size == 4) {
					/* We know we have to load the pc, don't do it twice */
					reglist = tp->ftt_instr2 & 0x7FFF;
				} else {
					reglist = tp->ftt_instr1 & 0xFF;
				}
			} else {
				/* We know we have to load the pc, don't do it twice */
				reglist = tp->ftt_instr & 0x7FFF;
			}

			base = (uintptr_t*) regs->sp;
			while (reglist) {
				if (reglist & 1) {
					ret = fasttrap_fuword32((uint32_t) base, &regs->r[regnum]);
					if (ret == -1) {
						fasttrap_sigsegv(p, uthread, (user_addr_t) base, regs);
						new_pc = regs->pc;
						break;
					}
					base++;
				}
				reglist >>= 1;
				regnum++;
			}

			ret = fasttrap_fuword32((uint32_t) base, &new_pc);
			if (ret == -1) {
				fasttrap_sigsegv(p, uthread, (user_addr_t) base, regs);
				new_pc = regs->pc;
				break;
			}
			base++;

			regs->sp = (uintptr_t) base;

			set_thumb_flag(regs, new_pc);

			break;
		}

		case FASTTRAP_T_CB_N_Z:
		{
			/* Thumb mode instruction, and not permitted in IT block, so skip the condition code check */
			int rn = tp->ftt_instr1 & 0x7;
			int offset = (((tp->ftt_instr1 & 0x00F8) >> 2) | ((tp->ftt_instr1 & 0x0200) >> 3)) + 4;
			int nonzero = tp->ftt_instr1 & 0x0800;
			if (!nonzero != !(regs->r[rn] == 0)) {
				new_pc = pc + offset;
			} else {
				new_pc = pc + instr_size;
			}
			break;
		}

		case FASTTRAP_T_B_COND:
		{
			/* Use the condition code in the instruction and ignore the ITSTATE */

			int code, offset;
			if (tp->ftt_thumb) {
				if (instr_size == 4) {
					code = (tp->ftt_instr1 >> 6) & 0xF;
					if (code == 14 || code == 15) {
						panic("fasttrap: Emulation of invalid branch");
					}
					int S = (tp->ftt_instr1 >> 10) & 1,
					    J1 = (tp->ftt_instr2 >> 13) & 1,
					    J2 = (tp->ftt_instr2 >> 11) & 1;
					offset = 4 + SIGNEXTEND(
					    (S << 20) | (J2 << 19) | (J1 << 18) |
					    ((tp->ftt_instr1 & 0x003F) << 12) |
					    ((tp->ftt_instr2 & 0x07FF) << 1),
					    21);
				} else {
					code = (tp->ftt_instr1 >> 8) & 0xF;
					if (code == 14 || code == 15) {
						panic("fasttrap: Emulation of invalid branch");
					}
					offset = 4 + (SIGNEXTEND(tp->ftt_instr1 & 0xFF, 8) << 1);
				}
			} else {
				code = ARM_CONDCODE(tp->ftt_instr);
				if (code == 15) {
					panic("fasttrap: Emulation of invalid branch");
				}
				offset = 8 + (SIGNEXTEND(tp->ftt_instr & 0x00FFFFFF, 24) << 2);
			}

			if (dtrace_arm_condition_true(code, regs->cpsr)) {
				new_pc = pc + offset;
			} else {
				new_pc = pc + instr_size;
			}

			break;
		}

		case FASTTRAP_T_B_UNCOND:
		{
			int offset;

			/* Unconditional branches can only be taken from Thumb mode */
			/* (This is different from an ARM branch with condition code "always") */
			ASSERT(tp->ftt_thumb == 1);

			if (!dtrace_arm_condition_true(condition_code, regs->cpsr)) {
				new_pc = pc + instr_size;
				break;
			}

			if (instr_size == 4) {
				int S = (tp->ftt_instr1 >> 10) & 1,
				    J1 = (tp->ftt_instr2 >> 13) & 1,
				    J2 = (tp->ftt_instr2 >> 11) & 1;
				int I1 = (J1 != S) ? 0 : 1, I2 = (J2 != S) ? 0 : 1;
				offset = 4 + SIGNEXTEND(
				    (S << 24) | (I1 << 23) | (I2 << 22) |
				    ((tp->ftt_instr1 & 0x03FF) << 12) |
				    ((tp->ftt_instr2 & 0x07FF) << 1),
				    25);
			} else {
				uint32_t instr1 = tp->ftt_instr1;
				offset = 4 + (SIGNEXTEND(instr1 & 0x7FF, 11) << 1);
			}

			new_pc = pc + offset;

			break;
		}

		case FASTTRAP_T_BX_REG:
		{
			int reg;

			if (!dtrace_arm_condition_true(condition_code, regs->cpsr)) {
				new_pc = pc + instr_size;
				break;
			}

			if (tp->ftt_thumb) {
				reg = THUMB16_HRM(tp->ftt_instr1);
			} else {
				reg = ARM_RM(tp->ftt_instr);
			}
			new_pc = regs->r[reg];
			set_thumb_flag(regs, new_pc);

			break;
		}

		case FASTTRAP_T_LDR_PC_IMMED:
		case FASTTRAP_T_VLDR_PC_IMMED:
			/* Handle these instructions by replacing the PC in the instruction with another
			 * register. They are common, so we'd like to support them, and this way we do so
			 * without any risk of having to simulate a segfault.
			 */

			/* Fall through */

		instr_emulate:
		case FASTTRAP_T_COMMON:
		{
			user_addr_t addr;
			uint8_t scratch[32];
			uint_t i = 0;
			fasttrap_instr_t emul_instr;
			emul_instr.instr32 = tp->ftt_instr;
			int emul_instr_size;

			/*
			 * Unfortunately sometimes when we emulate the instruction and have to replace the
			 * PC, there is no longer a thumb mode equivalent. We end up having to run the
			 * modified instruction in ARM mode. We use this variable to keep track of which
			 * mode we should emulate in. We still use the original variable to determine
			 * what mode to return to.
			 */
			uint8_t emul_thumb = tp->ftt_thumb;
			int save_reg = -1;
			uint32_t save_val = 0;

			/*
			 * Dealing with condition codes and emulation:
			 * We can't just uniformly do a condition code check here because not all instructions
			 * have condition codes. We currently do not support an instruction by instruction trace,
			 * so we can assume that either: 1. We are executing a Thumb instruction, in which case
			 * we either are not in an IT block and should execute always, or we are last in an IT
			 * block. Either way, the traced instruction will run correctly, and we won't have any
			 * problems when we return to the original code, because we will no longer be in the IT
			 * block. 2. We are executing an ARM instruction, in which case we are ok as long as
			 * we don't attempt to change the condition code.
			 */
			if (tp->ftt_type == FASTTRAP_T_LDR_PC_IMMED) {
				/* We know we always have a free register (the one we plan to write the
				 * result value to!). So we'll replace the pc with that one.
				 */
				int new_reg;
				if (tp->ftt_thumb) {
					/* Check to see if thumb or thumb2 */
					if (instr_size == 2) {
						/*
						 * Sadness. We need to emulate this instruction in ARM mode
						 * because it has an 8 bit immediate offset. Instead of having
						 * to deal with condition codes in the ARM instruction, we'll
						 * just check the condition and abort if the condition is false.
						 */
						if (!dtrace_arm_condition_true(condition_code, regs->cpsr)) {
							new_pc = pc + instr_size;
							break;
						}

						new_reg = (tp->ftt_instr1 >> 8) & 0x7;
						regs->r[new_reg] = ALIGNADDR(regs->pc + 4, 2);
						emul_thumb = 0;
						emul_instr.instr32 = 0xE5900000 | (new_reg << 16) | (new_reg << 12) | ((tp->ftt_instr1 & 0xFF) << 2);
					} else {
						/* Thumb2. Just replace the register. */
						new_reg = (tp->ftt_instr2 >> 12) & 0xF;
						regs->r[new_reg] = ALIGNADDR(regs->pc + 4, 2);
						emul_instr.instr16.instr1 &= ~0x000F;
						emul_instr.instr16.instr1 |= new_reg;
					}
				} else {
					/* ARM. Just replace the register. */
					new_reg = (tp->ftt_instr >> 12) & 0xF;
					regs->r[new_reg] = ALIGNADDR(regs->pc + 8,2);
					emul_instr.instr32 &= ~0x000F0000;
					emul_instr.instr32 |= new_reg << 16;
				}
			} else if (tp->ftt_type == FASTTRAP_T_VLDR_PC_IMMED) {
				/* This instruction only uses one register, and if we're here, we know
				 * it must be the pc. So we'll just replace it with R0.
				 */
				save_reg = 0;
				save_val = regs->r[0];
				regs->r[save_reg] = ALIGNADDR(regs->pc + (tp->ftt_thumb ? 4 : 8), 2);
				if (tp->ftt_thumb) {
					emul_instr.instr16.instr1 &= ~0x000F;
				} else {
					emul_instr.instr32 &= ~0x000F0000;
				}
			}

			emul_instr_size = dtrace_instr_size(emul_instr.instr32, emul_thumb);

			/*
			 * At this point:
			 *   tp->ftt_thumb = thumb mode of original instruction
			 *   emul_thumb = thumb mode for emulation
			 *   emul_instr = instruction we are using to emulate original instruction
			 *   emul_instr_size = size of emulating instruction
			 */

			addr = uthread->t_dtrace_scratch->addr;

			if (addr == 0LL) {
				fasttrap_sigtrap(p, uthread, pc); // Should be killing target proc
				new_pc = pc;
				break;
			}

			uthread->t_dtrace_scrpc = addr;
			if (emul_thumb) {
				/*
				 * No way to do an unconditional branch in Thumb mode, shove the address
				 * onto the user stack and go to the next location with a pop. This can
				 * segfault if this push happens to cross a stack page, but that's ok, since
				 * we are running in userland, and the kernel knows how to handle userland
				 * stack expansions correctly.
				 *
				 * Layout of scratch space for Thumb mode:
				 *   Emulated instruction
				 *   ldr save_reg, [pc, #16] (if necessary, restore any register we clobbered)
				 *   push { r0, r1 }
				 *   ldr r0, [pc, #4]
				 *   str r0, [sp, #4]
				 *   pop { r0, pc }
				 *   Location we should return to in original program
				 *   Saved value of clobbered register (if necessary)
				 */

				bcopy(&emul_instr, &scratch[i], emul_instr_size); i += emul_instr_size;

				if (save_reg != -1) {
					uint16_t restore_inst = 0x4803;
					restore_inst |= (save_reg & 0x7) << 8;
					SET16(scratch+i, restore_inst); i += 2;		// ldr reg, [pc , #16]
				}

				SET16(scratch+i, 0xB403); i += 2;			// push { r0, r1 }
				SET16(scratch+i, 0x4801); i += 2;			// ldr r0, [pc, #4]
				SET16(scratch+i, 0x9001); i += 2;			// str r0, [sp, #4]
				SET16(scratch+i, 0xBD01); i += 2;			// pop { r0, pc }

				if (i % 4) {
					SET16(scratch+i, 0); i += 2;			// padding - saved 32 bit words must be aligned
				}
				SET32(scratch+i, pc + instr_size + (tp->ftt_thumb ? 1 : 0)); i += 4;	// Return address
				if (save_reg != -1) {
					SET32(scratch+i, save_val); i += 4;		// saved value of clobbered register
				}

				uthread->t_dtrace_astpc = addr + i;
				bcopy(&emul_instr, &scratch[i], emul_instr_size); i += emul_instr_size;
				SET16(scratch+i, FASTTRAP_THUMB_RET_INSTR); i += 2;
			} else {
				/*
				 * Layout of scratch space for ARM mode:
				 *   Emulated instruction
				 *   ldr save_reg, [pc, #12] (if necessary, restore any register we clobbered)
				 *   ldr pc, [pc, #4]
				 *   Location we should return to in original program
				 *   Saved value of clobbered register (if necessary)
				 */

				bcopy(&emul_instr, &scratch[i], emul_instr_size); i += emul_instr_size;

				if (save_reg != -1) {
					uint32_t restore_inst = 0xE59F0004;
					restore_inst |= save_reg << 12;
					SET32(scratch+i, restore_inst); i += 4;		// ldr reg, [pc, #12]
				}
				SET32(scratch+i, 0xE51FF004); i += 4;			// ldr pc, [pc, #4]

				SET32(scratch+i, pc + instr_size + (tp->ftt_thumb ? 1 : 0)); i += 4;	// Return address
				if (save_reg != -1) {
					SET32(scratch+i, save_val); i += 4;		// Saved value of clobbered register
				}

				uthread->t_dtrace_astpc = addr + i;
				bcopy(&emul_instr, &scratch[i], emul_instr_size); i += emul_instr_size;
				SET32(scratch+i, FASTTRAP_ARM_RET_INSTR); i += 4;
			}

			if (uwrite(p, scratch, i, uthread->t_dtrace_scratch->write_addr) != KERN_SUCCESS) {
				fasttrap_sigtrap(p, uthread, pc);
				new_pc = pc;
				break;
			}

			if (tp->ftt_retids != NULL) {
				uthread->t_dtrace_step = 1;
				uthread->t_dtrace_ret = 1;
				new_pc = uthread->t_dtrace_astpc + (emul_thumb ? 1 : 0);
			} else {
				new_pc = uthread->t_dtrace_scrpc + (emul_thumb ? 1 : 0);
			}

			uthread->t_dtrace_pc = pc;
			uthread->t_dtrace_npc = pc + instr_size;
			uthread->t_dtrace_on = 1;
			was_simulated = 0;
			set_thumb_flag(regs, new_pc);
			break;
		}

		default:
			panic("fasttrap: mishandled an instruction");
	}

done:
	/*
	 * APPLE NOTE:
	 *
	 * We're setting this earlier than Solaris does, to get a "correct"
	 * ustack() output. In the Sun code,  a() -> b() -> c() -> d() is
	 * reported at: d, b, a. The new way gives c, b, a, which is closer
	 * to correct, as the return instruction has already exectued.
	 */
	regs->pc = new_pc;

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
			fasttrap_return_common(p, regs, pc, new_pc);
		} else {
			ASSERT(uthread->t_dtrace_ret != 0);
			ASSERT(uthread->t_dtrace_pc == pc);
			ASSERT(uthread->t_dtrace_scrpc != 0);
			ASSERT(new_pc == uthread->t_dtrace_astpc);
		}
	}

	return (0);
}