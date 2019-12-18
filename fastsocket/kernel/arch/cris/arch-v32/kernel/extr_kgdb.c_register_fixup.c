#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int sp; int pc; int erp; int spc; int exs; scalar_t__ eda; } ;

/* Variables and functions */
 int SIGINT ; 
 int SIGTRAP ; 
 int dynamic_bp ; 
 int insn_size (int) ; 
 TYPE_1__ reg ; 

void register_fixup(int sigval)
{
	/* Compensate for ACR push at the beginning of exception handler. */
	reg.sp += 4;

	/* Standard case. */
	reg.pc = reg.erp;
	if (reg.erp & 0x1) {
		/* Delay slot bit set.  Report as stopped on proper instruction.  */
		if (reg.spc) {
			/* Rely on SPC if set. */
			reg.pc = reg.spc;
		} else {
			/* Calculate the PC from the size of the instruction
			   that the delay slot we're in belongs to. */
			reg.pc += insn_size(reg.erp & ~1) - 1 ;
		}
	}

	if ((reg.exs & 0x3) == 0x0) {
		/* Bits 1 - 0 indicate the type of memory operation performed
		   by the interrupted instruction. 0 means no memory operation,
		   and EDA is undefined in that case. We zero it to avoid confusion. */
		reg.eda = 0;
	}

	if (sigval == SIGTRAP) {
		/* Break 8, single step or hardware breakpoint exception. */

		/* Check IDX field of EXS. */
		if (((reg.exs & 0xff00) >> 8) == 0x18) {

			/* Break 8. */

                        /* Static (compiled) breakpoints must return to the next instruction
			   in order to avoid infinite loops (default value of ERP). Dynamic
			   (gdb-invoked) must subtract the size of the break instruction from
			   the ERP so that the instruction that was originally in the break
			   instruction's place will be run when we return from the exception. */
			if (!dynamic_bp) {
				/* Assuming that all breakpoints are dynamic from now on. */
				dynamic_bp = 1;
			} else {

				/* Only if not in a delay slot. */
				if (!(reg.erp & 0x1)) {
					reg.erp -= 2;
					reg.pc -= 2;
				}
			}

		} else if (((reg.exs & 0xff00) >> 8) == 0x3) {
			/* Single step. */
			/* Don't fiddle with S1. */

		} else if (((reg.exs & 0xff00) >> 8) == 0xc) {

			/* Hardware watchpoint exception. */

			/* SPC has been updated so that we will get a single step exception
			   when we return, but we don't want that. */
			reg.spc = 0;

			/* Don't fiddle with S1. */
		}

	} else if (sigval == SIGINT) {
		/* Nothing special. */
	}
}