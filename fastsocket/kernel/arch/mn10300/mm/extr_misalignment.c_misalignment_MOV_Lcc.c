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
typedef  int uint32_t ;
struct pt_regs {unsigned long epsw; scalar_t__ lar; scalar_t__ pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned long EPSW_FLAG_C ; 
 unsigned long EPSW_FLAG_Z ; 
 int /*<<< orphan*/  kdebug (char*,int,...) ; 

__attribute__((used)) static void misalignment_MOV_Lcc(struct pt_regs *regs, uint32_t opcode)
{
	unsigned long epsw = regs->epsw;
	unsigned long NxorV;

	kdebug("MOV_Lcc %x [flags=%lx]", opcode, epsw & 0xf);

	/* calculate N^V and shift onto the same bit position as Z */
	NxorV = ((epsw >> 3) ^ epsw >> 1) & 1;

	switch (opcode & 0xf) {
	case 0x0: /* MOV_LLT: N^V */
		if (NxorV)
			goto take_the_loop;
		return;
	case 0x1: /* MOV_LGT: ~(Z or (N^V))*/
		if (!((epsw & EPSW_FLAG_Z) | NxorV))
			goto take_the_loop;
		return;
	case 0x2: /* MOV_LGE: ~(N^V) */
		if (!NxorV)
			goto take_the_loop;
		return;
	case 0x3: /* MOV_LLE: Z or (N^V) */
		if ((epsw & EPSW_FLAG_Z) | NxorV)
			goto take_the_loop;
		return;

	case 0x4: /* MOV_LCS: C */
		if (epsw & EPSW_FLAG_C)
			goto take_the_loop;
		return;
	case 0x5: /* MOV_LHI: ~(C or Z) */
		if (!(epsw & (EPSW_FLAG_C | EPSW_FLAG_Z)))
			goto take_the_loop;
		return;
	case 0x6: /* MOV_LCC: ~C */
		if (!(epsw & EPSW_FLAG_C))
			goto take_the_loop;
		return;
	case 0x7: /* MOV_LLS: C or Z */
		if (epsw & (EPSW_FLAG_C | EPSW_FLAG_Z))
			goto take_the_loop;
		return;

	case 0x8: /* MOV_LEQ: Z */
		if (epsw & EPSW_FLAG_Z)
			goto take_the_loop;
		return;
	case 0x9: /* MOV_LNE: ~Z */
		if (!(epsw & EPSW_FLAG_Z))
			goto take_the_loop;
		return;
	case 0xa: /* MOV_LRA: always */
		goto take_the_loop;

	default:
		BUG();
	}

take_the_loop:
	/* wind the PC back to just after the SETLB insn */
	kdebug("loop LAR=%lx", regs->lar);
	regs->pc = regs->lar - 4;
}