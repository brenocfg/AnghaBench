#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pt_regs {unsigned long nip; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_SIAR ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 unsigned long perf_ip_adjust (struct pt_regs*) ; 
 int regs_use_siar (struct pt_regs*) ; 
 scalar_t__ siar_valid (struct pt_regs*) ; 

unsigned long perf_instruction_pointer(struct pt_regs *regs)
{
	bool use_siar = regs_use_siar(regs);

	if (use_siar && siar_valid(regs))
		return mfspr(SPRN_SIAR) + perf_ip_adjust(regs);
	else if (use_siar)
		return 0;		// no valid instruction pointer
	else
		return regs->nip;
}