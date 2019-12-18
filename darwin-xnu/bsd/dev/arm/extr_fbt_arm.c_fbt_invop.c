#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct arm_vfpsaved_state {int dummy; } ;
struct arm_saved_state {int sp; int cpsr; uintptr_t* r; scalar_t__ lr; } ;
struct TYPE_4__ {scalar_t__ fbtp_roffset; int fbtp_savedval; int /*<<< orphan*/  fbtp_id; scalar_t__ fbtp_patchpoint; struct TYPE_4__* fbtp_hashnext; } ;
typedef  TYPE_1__ fbt_probe_t ;
struct TYPE_5__ {int cpu_dtrace_invop_underway; scalar_t__ cpu_dtrace_caller; } ;

/* Variables and functions */
 TYPE_3__* CPU ; 
 int DTRACE_INVOP_NOP ; 
 size_t FBT_ADDR2NDX (uintptr_t) ; 
 scalar_t__ FBT_IS_THUMB_SET_R7 (int) ; 
 int FBT_THUMB_SET_R7_OFFSET (int) ; 
 int PSR_FIQ_MODE ; 
 int PSR_MODE_MASK ; 
 int VFPSAVE_ALIGN_DTRACE ; 
 int /*<<< orphan*/  clear_itstate (int*) ; 
 scalar_t__ dtrace_arm_condition_true (int,int) ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ; 
 TYPE_1__** fbt_probetab ; 
 int get_itstate (int) ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 

int
fbt_invop(uintptr_t addr, uintptr_t * stack, uintptr_t rval)
{
	fbt_probe_t    *fbt = fbt_probetab[FBT_ADDR2NDX(addr)];

	for (; fbt != NULL; fbt = fbt->fbtp_hashnext) {
		if ((uintptr_t) fbt->fbtp_patchpoint == addr) {
			if (0 == CPU->cpu_dtrace_invop_underway) {
				CPU->cpu_dtrace_invop_underway = 1;	/* Race not possible on
									 * this per-cpu state */

				struct arm_saved_state* regs = (struct arm_saved_state*) stack;
				uintptr_t stack4 = *((uintptr_t*) regs->sp);

				if ((regs->cpsr & PSR_MODE_MASK) == PSR_FIQ_MODE) {
					/*
					 * We do not handle probes firing from FIQ context. We used to
					 * try to undo the patch and rerun the instruction, but
					 * most of the time we can't do that successfully anyway.
					 * Instead, we just panic now so we fail fast.
					 */
					panic("dtrace: fbt: The probe at %08x was called from FIQ_MODE",(unsigned) addr);
				}

				/*
				 * If we are not outside an IT block, and are not executing the last instruction of an IT block,
				 * then that is an instrumentation error or a code gen error. Either way, we panic.
				 */
				uint32_t itstate = get_itstate(regs->cpsr);
				if ((itstate & 0x7) != 0) {
					panic("dtrace: fbt: Instruction stream error: Middle of IT block at %08x",(unsigned) addr);
				}

				if (fbt->fbtp_roffset == 0) {
					/*
						We need the frames to set up the backtrace, but we won't have the frame pointers
						until after the instruction is emulated. So here we calculate the address of the
						frame pointer from the saved instruction and put it in the stack. Yes, we end up
						repeating this work again when we emulate the instruction.

						This assumes that the frame area is immediately after the saved reg storage!
					*/
					uint32_t offset = ((uint32_t) regs) + sizeof(struct arm_saved_state);
#if __ARM_VFP__
					/* Match the stack alignment required for arm_vfpsaved_state */
					offset &= ~(VFPSAVE_ALIGN_DTRACE - 1);
					offset += VFPSAVE_ALIGN_DTRACE + sizeof(struct arm_vfpsaved_state);
#endif /* __ARM_VFP__ */
					if (FBT_IS_THUMB_SET_R7(fbt->fbtp_savedval))
						*((uint32_t*) offset) = regs->sp + FBT_THUMB_SET_R7_OFFSET(fbt->fbtp_savedval);
					else
						*((uint32_t*) offset) = regs->sp;

					CPU->cpu_dtrace_caller = regs->lr;
					dtrace_probe(fbt->fbtp_id, regs->r[0], regs->r[1], regs->r[2], regs->r[3], stack4);
					CPU->cpu_dtrace_caller = 0;
				} else {
					/* Check to see if we're in the middle of an IT block. */
					if (itstate != 0) {
						/*
						 * We've already checked previously to see how far we are in the IT block.
						 * Here we must be getting ready to execute the last instruction.
						 */
						int condition_it = (itstate & 0xF0) >> 4;

						if (dtrace_arm_condition_true(condition_it, regs->cpsr) == 0) {
							/* Condition wasn't true, so becomes a nop. */
							clear_itstate(&regs->cpsr);
							CPU->cpu_dtrace_invop_underway = 0;
							return DTRACE_INVOP_NOP;
						}
					}

					dtrace_probe(fbt->fbtp_id, fbt->fbtp_roffset, rval, 0, 0, 0);
					CPU->cpu_dtrace_caller = 0;

					/* The dtrace script may access cpsr, so make sure to clear only after probe fired. */
					clear_itstate(&regs->cpsr);
				}
				CPU->cpu_dtrace_invop_underway = 0;
			}

			/*
				On other architectures, we return a DTRACE constant to let the callback function
				know what was replaced. On the ARM, since the function prologue/epilogue machine code
				can vary, we need the actual bytes of the instruction, so return the savedval instead.
			*/
			return (fbt->fbtp_savedval);
		}
	}

	return (0);
}