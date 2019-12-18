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
struct pt_regs {int msr; scalar_t__ nip; } ;
struct bpt {int /*<<< orphan*/  ref_count; scalar_t__ address; } ;

/* Variables and functions */
 int MSR_IR ; 
 int MSR_PR ; 
 int MSR_SF ; 
 struct bpt* at_breakpoint (scalar_t__) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct bpt* in_breakpoint_table (scalar_t__,unsigned long*) ; 
 int /*<<< orphan*/  xmon_core (struct pt_regs*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xmon_bpt(struct pt_regs *regs)
{
	struct bpt *bp;
	unsigned long offset;

	if ((regs->msr & (MSR_IR|MSR_PR|MSR_SF)) != (MSR_IR|MSR_SF))
		return 0;

	/* Are we at the trap at bp->instr[1] for some bp? */
	bp = in_breakpoint_table(regs->nip, &offset);
	if (bp != NULL && offset == 4) {
		regs->nip = bp->address + 4;
		atomic_dec(&bp->ref_count);
		return 1;
	}

	/* Are we at a breakpoint? */
	bp = at_breakpoint(regs->nip);
	if (!bp)
		return 0;

	xmon_core(regs, 0);

	return 1;
}