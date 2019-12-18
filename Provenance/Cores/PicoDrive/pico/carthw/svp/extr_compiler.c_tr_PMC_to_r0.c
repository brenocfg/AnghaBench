#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  l; } ;
struct TYPE_4__ {int emu_status; TYPE_1__ pmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_COND_EQ ; 
 int /*<<< orphan*/  A_COND_NE ; 
 int /*<<< orphan*/  A_OP_BIC ; 
 int /*<<< orphan*/  A_OP_ORR ; 
 int /*<<< orphan*/  EOP_C_DOP_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EOP_LDR_IMM (int,int,int) ; 
 int /*<<< orphan*/  EOP_STR_IMM (int,int,int) ; 
 int /*<<< orphan*/  EOP_TST_IMM (int,int /*<<< orphan*/ ,int) ; 
 int KRREG_PMC ; 
 int SSP_PMC ; 
 int SSP_PMC_HAVE_ADDR ; 
 int SSP_PMC_SET ; 
 int* hostreg_r ; 
 int known_regb ; 
 TYPE_2__ known_regs ; 
 int /*<<< orphan*/  tr_flush_dirty_ST () ; 
 int /*<<< orphan*/  tr_mov16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tr_PMC_to_r0(int op)
{
	if (known_regb & KRREG_PMC)
	{
		if (known_regs.emu_status & SSP_PMC_HAVE_ADDR) {
			known_regs.emu_status |= SSP_PMC_SET;
			known_regs.emu_status &= ~SSP_PMC_HAVE_ADDR;
			// do nothing - this is handled elsewhere
		} else {
			tr_mov16(0, known_regs.pmc.l);
			known_regs.emu_status |= SSP_PMC_HAVE_ADDR;
		}
	}
	else
	{
		EOP_LDR_IMM(1,7,0x484);			// ldr r1, [r7, #0x484] // emu_status
		tr_flush_dirty_ST();
		if (op != 0x000e)
			EOP_LDR_IMM(0, 7, 0x400+SSP_PMC*4);
		EOP_TST_IMM(1, 0, SSP_PMC_HAVE_ADDR);
		EOP_C_DOP_IMM(A_COND_EQ,A_OP_ORR,0, 1, 1, 0, SSP_PMC_HAVE_ADDR); // orreq r1, r1, #..
		EOP_C_DOP_IMM(A_COND_NE,A_OP_BIC,0, 1, 1, 0, SSP_PMC_HAVE_ADDR); // bicne r1, r1, #..
		EOP_C_DOP_IMM(A_COND_NE,A_OP_ORR,0, 1, 1, 0, SSP_PMC_SET);       // orrne r1, r1, #..
		EOP_STR_IMM(1,7,0x484);
		hostreg_r[0] = hostreg_r[1] = -1;
	}
}