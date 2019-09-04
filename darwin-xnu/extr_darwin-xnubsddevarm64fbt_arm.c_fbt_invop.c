#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fbtp_roffset; int fbtp_savedval; int /*<<< orphan*/  fbtp_id; scalar_t__ fbtp_patchpoint; struct TYPE_5__* fbtp_hashnext; } ;
typedef  TYPE_1__ fbt_probe_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_6__ {int /*<<< orphan*/  ss; } ;
typedef  TYPE_2__ arm_context_t ;
struct TYPE_7__ {int cpu_dtrace_invop_underway; void* cpu_dtrace_caller; } ;

/* Variables and functions */
 TYPE_4__* CPU ; 
 size_t FBT_ADDR2NDX (uintptr_t) ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t,uintptr_t) ; 
 TYPE_1__** fbt_probetab ; 
 void* get_saved_state_lr (int /*<<< orphan*/ *) ; 
 uintptr_t get_saved_state_reg (int /*<<< orphan*/ *,int) ; 

int
fbt_invop(uintptr_t addr, uintptr_t * stack, uintptr_t rval)
{
	fbt_probe_t    *fbt = fbt_probetab[FBT_ADDR2NDX(addr)];

	for (; fbt != NULL; fbt = fbt->fbtp_hashnext) {
		if ((uintptr_t) fbt->fbtp_patchpoint == addr) {
			if (0 == CPU->cpu_dtrace_invop_underway) {
				CPU->cpu_dtrace_invop_underway = 1;	/* Race not possible on
									 * this per-cpu state */

				if (fbt->fbtp_roffset == 0) {
					/*
					 * Stack looks like this:
					 *
					 *	[Higher addresses]
					 *
					 *	Frame of caller
					 *	Extra args for callee
					 *	------------------------
					 *	Frame from traced function: <previous sp (e.g. 0x1000), return address>
					 *	------------------------
					 *	arm_context_t
					 *	------------------------
					 *	Frame from trap handler:  <previous sp (e.g. 0x1000) , traced PC >
					 *				The traced function never got to mov fp, sp,
					 *				so there is no frame in the backtrace pointing
					 *				to the frame on the stack containing the LR in the
					 *				caller.
					 *	------------------------
					 *	     |
					 *	     |
					 *	     |  stack grows this way
					 *	     |
					 *	     |
					 *	     v
					 *	[Lower addresses]
					 */

					arm_saved_state_t *regs = (arm_saved_state_t *)(&((arm_context_t *)stack)->ss);

					/*
					 * cpu_dtrace_caller compensates for fact that the traced function never got to update its fp.
					 * When walking the stack, when we reach the frame where we extract a PC in the patched
					 * function, we put the cpu_dtrace_caller in the backtrace instead.  The next frame we extract
					 * will be in the caller's caller, so we output a backtrace starting at the caller and going
					 * sequentially up the stack.
					 */
					CPU->cpu_dtrace_caller = get_saved_state_lr(regs);
					dtrace_probe(fbt->fbtp_id, get_saved_state_reg(regs, 0), get_saved_state_reg(regs, 1),
					    get_saved_state_reg(regs, 2), get_saved_state_reg(regs, 3),get_saved_state_reg(regs, 4));
					CPU->cpu_dtrace_caller = 0;
				} else {
					/*
					 * When fbtp_roffset is non-zero, we know we are handling a return probe point.
					 *
					 *
					 * Stack looks like this, as we've already popped the frame in the traced callee, and
					 * we trap with lr set to the return address in the caller.
					 *	[Higher addresses]
					 *
					 *	Frame of caller
					 *	Extra args for callee
					 *	------------------------
					 *	arm_context_t
					 *	------------------------
					 *	Frame from trap handler:  <sp at time of trap, traced PC >
					 *	------------------------
					 *	     |
					 *	     |
					 *	     |  stack grows this way
					 *	     |
					 *	     |
					 *	     v
					 *	[Lower addresses]
					 */
					arm_saved_state_t *regs = (arm_saved_state_t *)(&((arm_context_t *)stack)->ss);

					CPU->cpu_dtrace_caller = get_saved_state_lr(regs);
					dtrace_probe(fbt->fbtp_id, fbt->fbtp_roffset, rval, 0, 0, 0);
					CPU->cpu_dtrace_caller = 0;
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