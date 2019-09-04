#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* uthread_t ;
typedef  long long user_addr_t ;
typedef  size_t uint_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_19__ {int ftt_thumb; int ftt_instr; int ftt_type; int ftt_instr1; int ftt_instr2; int /*<<< orphan*/ * ftt_retids; } ;
typedef  TYPE_4__ fasttrap_tracepoint_t ;
struct TYPE_16__ {int instr1; } ;
struct TYPE_20__ {int instr32; TYPE_1__ instr16; } ;
typedef  TYPE_5__ fasttrap_instr_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_21__ {int pc; int* r; int sp; int lr; int /*<<< orphan*/  cpsr; } ;
typedef  TYPE_6__ arm_saved_state32_t ;
struct TYPE_18__ {long long t_dtrace_scrpc; long long t_dtrace_astpc; int t_dtrace_step; int t_dtrace_ret; int t_dtrace_pc; int t_dtrace_on; int /*<<< orphan*/  t_dtrace_npc; TYPE_2__* t_dtrace_scratch; } ;
struct TYPE_17__ {long long addr; int /*<<< orphan*/  write_addr; } ;

/* Variables and functions */
 void* ALIGNADDR (int,int) ; 
 int ARM_CONDCODE (int) ; 
 int ARM_RM (int) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int FASTTRAP_ARM32_RET_INSTR ; 
 int FASTTRAP_THUMB32_RET_INSTR ; 
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
 scalar_t__ IS_ARM32_NOP (int) ; 
 scalar_t__ IS_THUMB32_NOP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  SET16 (int*,int) ; 
 int /*<<< orphan*/  SET32 (int*,int) ; 
 int SIGNEXTEND (int,int) ; 
 int THUMB16_HRM (int) ; 
 int /*<<< orphan*/  THUMB_INSTR (int) ; 
 int /*<<< orphan*/  bcopy (TYPE_5__*,int*,int) ; 
 int /*<<< orphan*/  condition_true (int,int /*<<< orphan*/ ) ; 
 int dtrace_instr_size (int,int) ; 
 int fasttrap_fuword32 (long long,int*) ; 
 int fasttrap_get_condition_code (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  fasttrap_sigsegv (int /*<<< orphan*/ *,TYPE_3__*,long long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fasttrap_sigtrap (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int fasttrap_suword32 (int,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_6__* saved_state32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_saved_state_pc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_thumb_flag (TYPE_6__*,int) ; 
 int /*<<< orphan*/  uwrite (int /*<<< orphan*/ *,int*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void 
fasttrap_pid_probe_handle_patched_instr32(arm_saved_state_t *state, fasttrap_tracepoint_t *tp, uthread_t uthread, 
		proc_t *p, uint_t is_enabled, int *was_simulated)
{
	arm_saved_state32_t *regs32 = saved_state32(state);
	uint32_t new_pc = 0;
	uint32_t pc = regs32->pc;
	int instr_size;
	int condition_code;

	*was_simulated = 1;

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
		regs32->r[0] = 1;
		new_pc = regs32->pc + (tp->ftt_thumb ? 2 : 4);
		goto done;
	}

	/* For USDT probes, bypass all the emulation logic for the nop instruction */
	if ((tp->ftt_thumb && IS_THUMB32_NOP(THUMB_INSTR(tp->ftt_instr))) ||
	    (!tp->ftt_thumb && IS_ARM32_NOP(tp->ftt_instr))) {
		new_pc = regs32->pc + (tp->ftt_thumb ? 2 : 4);
		goto done;
	}

	condition_code = fasttrap_get_condition_code(regs32, tp);
	instr_size = dtrace_instr_size(tp->ftt_instr,tp->ftt_thumb);

	switch (tp->ftt_type) {
		case FASTTRAP_T_MOV_PC_REG:
		case FASTTRAP_T_CPY_PC:
		{
			if (!condition_true(condition_code, regs32->cpsr)) {
				new_pc = pc + instr_size;
				break;
			}

			int rm;
			if (tp->ftt_thumb) {
				rm = THUMB16_HRM(tp->ftt_instr1);
			} else {
				rm = tp->ftt_instr & 0xF;
			}
			new_pc = regs32->r[rm];

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
			uint32_t base;

			if (!condition_true(condition_code, regs32->cpsr)) {
				new_pc = pc + instr_size;
				break;
			}

			base = regs32->sp;
			if (((base-16*4) >> PAGE_SHIFT) != (base >> PAGE_SHIFT)) {
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
			base -= 4;
			ret = fasttrap_suword32(base, regs32->lr);
			if (ret == -1) {
				fasttrap_sigsegv(p, uthread, (user_addr_t) base, state);
				new_pc = regs32->pc;
				break;
			}

			/* Start pushing from $r12 */
			int regmask = 1 << 12;
			int regnum = 12;

			while (regmask) {
				if (reglist & regmask) {
					base -= 4;
					ret = fasttrap_suword32(base, regs32->r[regnum]);
					if (ret == -1) {
						fasttrap_sigsegv(p, uthread, (user_addr_t) base, state);
						new_pc = regs32->pc;
						break;
					}
				}
				regmask >>= 1;
				regnum--;
			}

			regs32->sp = base;

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
			uint32_t base;

			if (!condition_true(condition_code, regs32->cpsr)) {
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

			base = regs32->sp;
			while (reglist) {
				if (reglist & 1) {
					ret = fasttrap_fuword32((user_addr_t)base, &regs32->r[regnum]);
					if (ret == -1) {
						fasttrap_sigsegv(p, uthread, (user_addr_t) base, state);
						new_pc = regs32->pc;
						break;
					}
					base += 4;
				}
				reglist >>= 1;
				regnum++;
			}

			ret = fasttrap_fuword32((user_addr_t)base, &new_pc);
			if (ret == -1) {
				fasttrap_sigsegv(p, uthread, (user_addr_t) base, state);
				new_pc = regs32->pc;
				break;
			}
			base += 4;

			regs32->sp = base;

			set_thumb_flag(regs32, new_pc);

			break;
		}

		case FASTTRAP_T_CB_N_Z:
		{
			/* Thumb mode instruction, and not permitted in IT block, so skip the condition code check */
			int rn = tp->ftt_instr1 & 0x7;
			int offset = (((tp->ftt_instr1 & 0x00F8) >> 2) | ((tp->ftt_instr1 & 0x0200) >> 3)) + 4;
			int nonzero = tp->ftt_instr1 & 0x0800;
			if (!nonzero != !(regs32->r[rn] == 0)) {
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

			if (condition_true(code, regs32->cpsr)) {
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

			if (!condition_true(condition_code, regs32->cpsr)) {
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

			if (!condition_true(condition_code, regs32->cpsr)) {
				new_pc = pc + instr_size;
				break;
			}

			if (tp->ftt_thumb) {
				reg = THUMB16_HRM(tp->ftt_instr1);
			} else {
				reg = ARM_RM(tp->ftt_instr);
			}
			new_pc = regs32->r[reg];
			set_thumb_flag(regs32, new_pc);

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
						if (!condition_true(condition_code, regs32->cpsr)) {
							new_pc = pc + instr_size;
							break;
						}

						new_reg = (tp->ftt_instr1 >> 8) & 0x7;
						regs32->r[new_reg] = ALIGNADDR(regs32->pc + 4, 2);
						emul_thumb = 0;
						emul_instr.instr32 = 0xE5900000 | (new_reg << 16) | (new_reg << 12) | ((tp->ftt_instr1 & 0xFF) << 2);
					} else {
						/* Thumb2. Just replace the register. */
						new_reg = (tp->ftt_instr2 >> 12) & 0xF;
						regs32->r[new_reg] = ALIGNADDR(regs32->pc + 4, 2);
						emul_instr.instr16.instr1 &= ~0x000F;
						emul_instr.instr16.instr1 |= new_reg;
					}
				} else {
					/* ARM. Just replace the register. */
					new_reg = (tp->ftt_instr >> 12) & 0xF;
					regs32->r[new_reg] = ALIGNADDR(regs32->pc + 8,2);
					emul_instr.instr32 &= ~0x000F0000;
					emul_instr.instr32 |= new_reg << 16;
				}
			} else if (tp->ftt_type == FASTTRAP_T_VLDR_PC_IMMED) {
				/* This instruction only uses one register, and if we're here, we know
				 * it must be the pc. So we'll just replace it with R0.
				 */
				save_reg = 0;
				save_val = regs32->r[0];
				regs32->r[save_reg] = ALIGNADDR(regs32->pc + (tp->ftt_thumb ? 4 : 8), 2);
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
				SET16(scratch+i, FASTTRAP_THUMB32_RET_INSTR); i += 2;
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
				SET32(scratch+i, FASTTRAP_ARM32_RET_INSTR); i += 4;
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
			*was_simulated = 0;
			set_thumb_flag(regs32, new_pc);
			break;
		}

		default:
			panic("fasttrap: mishandled an instruction");
	}
done:
	set_saved_state_pc(state, new_pc);	
	return;
}