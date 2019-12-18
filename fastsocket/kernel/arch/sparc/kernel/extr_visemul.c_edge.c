#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u16 ;
struct pt_regs {unsigned long tstate; } ;
struct TYPE_12__ {unsigned long left; unsigned long right; } ;
struct TYPE_11__ {unsigned long left; unsigned long right; } ;
struct TYPE_10__ {unsigned long left; unsigned long right; } ;
struct TYPE_9__ {unsigned long left; unsigned long right; } ;
struct TYPE_8__ {unsigned long left; unsigned long right; } ;
struct TYPE_7__ {unsigned long left; unsigned long right; } ;

/* Variables and functions */
#define  EDGE16LN_OPF 139 
#define  EDGE16L_OPF 138 
#define  EDGE16N_OPF 137 
#define  EDGE16_OPF 136 
#define  EDGE32LN_OPF 135 
#define  EDGE32L_OPF 134 
#define  EDGE32N_OPF 133 
#define  EDGE32_OPF 132 
#define  EDGE8LN_OPF 131 
#define  EDGE8L_OPF 130 
#define  EDGE8N_OPF 129 
#define  EDGE8_OPF 128 
 int /*<<< orphan*/  RD (unsigned int) ; 
 int /*<<< orphan*/  RS1 (unsigned int) ; 
 int /*<<< orphan*/  RS2 (unsigned int) ; 
 int /*<<< orphan*/  TIF_32BIT ; 
 unsigned long TSTATE_ICC ; 
 unsigned long TSTATE_XCC ; 
 TYPE_6__* edge16_tab ; 
 TYPE_5__* edge16_tab_l ; 
 TYPE_4__* edge32_tab ; 
 TYPE_3__* edge32_tab_l ; 
 TYPE_2__* edge8_tab ; 
 TYPE_1__* edge8_tab_l ; 
 unsigned long fetch_reg (int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  maybe_flush_windows (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_reg (struct pt_regs*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edge(struct pt_regs *regs, unsigned int insn, unsigned int opf)
{
	unsigned long orig_rs1, rs1, orig_rs2, rs2, rd_val;
	u16 left, right;

	maybe_flush_windows(RS1(insn), RS2(insn), RD(insn), 0);
	orig_rs1 = rs1 = fetch_reg(RS1(insn), regs);
	orig_rs2 = rs2 = fetch_reg(RS2(insn), regs);

	if (test_thread_flag(TIF_32BIT)) {
		rs1 = rs1 & 0xffffffff;
		rs2 = rs2 & 0xffffffff;
	}
	switch (opf) {
	default:
	case EDGE8_OPF:
	case EDGE8N_OPF:
		left = edge8_tab[rs1 & 0x7].left;
		right = edge8_tab[rs2 & 0x7].right;
		break;
	case EDGE8L_OPF:
	case EDGE8LN_OPF:
		left = edge8_tab_l[rs1 & 0x7].left;
		right = edge8_tab_l[rs2 & 0x7].right;
		break;

	case EDGE16_OPF:
	case EDGE16N_OPF:
		left = edge16_tab[(rs1 >> 1) & 0x3].left;
		right = edge16_tab[(rs2 >> 1) & 0x3].right;
		break;

	case EDGE16L_OPF:
	case EDGE16LN_OPF:
		left = edge16_tab_l[(rs1 >> 1) & 0x3].left;
		right = edge16_tab_l[(rs2 >> 1) & 0x3].right;
		break;

	case EDGE32_OPF:
	case EDGE32N_OPF:
		left = edge32_tab[(rs1 >> 2) & 0x1].left;
		right = edge32_tab[(rs2 >> 2) & 0x1].right;
		break;

	case EDGE32L_OPF:
	case EDGE32LN_OPF:
		left = edge32_tab_l[(rs1 >> 2) & 0x1].left;
		right = edge32_tab_l[(rs2 >> 2) & 0x1].right;
		break;
	};

	if ((rs1 & ~0x7UL) == (rs2 & ~0x7UL))
		rd_val = right & left;
	else
		rd_val = left;

	store_reg(regs, rd_val, RD(insn));

	switch (opf) {
	case EDGE8_OPF:
	case EDGE8L_OPF:
	case EDGE16_OPF:
	case EDGE16L_OPF:
	case EDGE32_OPF:
	case EDGE32L_OPF: {
		unsigned long ccr, tstate;

		__asm__ __volatile__("subcc	%1, %2, %%g0\n\t"
				     "rd	%%ccr, %0"
				     : "=r" (ccr)
				     : "r" (orig_rs1), "r" (orig_rs2)
				     : "cc");
		tstate = regs->tstate & ~(TSTATE_XCC | TSTATE_ICC);
		regs->tstate = tstate | (ccr << 32UL);
	}
	};
}