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
struct TYPE_3__ {int v; } ;
struct TYPE_4__ {int emu_status; int* pmac_write; TYPE_1__ pmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOP_LDR_IMM (int,int,int) ; 
 int /*<<< orphan*/  EOP_MOV_IMM (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EOP_STRH_REG (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  EOP_STR_IMM (int,int,int) ; 
 int KRREG_PMC ; 
 int SSP_PMC_HAVE_ADDR ; 
 int SSP_PMC_SET ; 
 int dirty_regb ; 
 int /*<<< orphan*/  emith_call_c_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emith_move_r_imm (int,int) ; 
 int get_inc (int) ; 
 int /*<<< orphan*/  hostreg_clear () ; 
 int* hostreg_r ; 
 int known_regb ; 
 TYPE_2__ known_regs ; 
 int /*<<< orphan*/  ssp_pm_write ; 
 int /*<<< orphan*/  tr_flush_dirty_ST () ; 
 int /*<<< orphan*/  tr_mov16 (int,int) ; 
 int /*<<< orphan*/  tr_unhandled () ; 

__attribute__((used)) static void tr_r0_to_PMX(int reg)
{
	if ((known_regb & KRREG_PMC) && (known_regs.emu_status & SSP_PMC_SET))
	{
		known_regs.pmac_write[reg] = known_regs.pmc.v;
		known_regs.emu_status &= ~SSP_PMC_SET;
		known_regb |= 1 << (25+reg);
		dirty_regb |= 1 << (25+reg);
		return;
	}

	if ((known_regb & KRREG_PMC) && (known_regb & (1 << (25+reg))))
	{
		int mode, addr;

		known_regs.emu_status &= ~SSP_PMC_HAVE_ADDR;

		mode = known_regs.pmac_write[reg]>>16;
		addr = known_regs.pmac_write[reg]&0xffff;
		if      ((mode & 0x43ff) == 0x0018) // DRAM
		{
			int inc = get_inc(mode);
			if (mode & 0x0400) tr_unhandled();
			EOP_LDR_IMM(1,7,0x490);		// dram_ptr
			emith_move_r_imm(2, addr << 1);
			EOP_STRH_REG(0,1,2);		// strh r0, [r1, r2]
			known_regs.pmac_write[reg] += inc;
		}
		else if ((mode & 0xfbff) == 0x4018) // DRAM, cell inc
		{
			if (mode & 0x0400) tr_unhandled();
			EOP_LDR_IMM(1,7,0x490);		// dram_ptr
			emith_move_r_imm(2, addr << 1);
			EOP_STRH_REG(0,1,2);		// strh r0, [r1, r2]
			known_regs.pmac_write[reg] += (addr&1) ? 31 : 1;
		}
		else if ((mode & 0x47ff) == 0x001c) // IRAM
		{
			int inc = get_inc(mode);
			EOP_LDR_IMM(1,7,0x48c);		// iram_ptr
			emith_move_r_imm(2, (addr&0x3ff) << 1);
			EOP_STRH_REG(0,1,2);		// strh r0, [r1, r2]
			EOP_MOV_IMM(1,0,1);
			EOP_STR_IMM(1,7,0x494);		// iram_dirty
			known_regs.pmac_write[reg] += inc;
		}
		else
			tr_unhandled();

		known_regs.pmc.v = known_regs.pmac_write[reg];
		//known_regb |= KRREG_PMC;
		dirty_regb |= KRREG_PMC;
		dirty_regb |= 1 << (25+reg);
		hostreg_r[1] = hostreg_r[2] = -1;
		return;
	}

	known_regb &= ~KRREG_PMC;
	dirty_regb &= ~KRREG_PMC;
	known_regb &= ~(1 << (25+reg));
	dirty_regb &= ~(1 << (25+reg));

	// call the C code to handle this
	tr_flush_dirty_ST();
	//tr_flush_dirty_pmcrs();
	tr_mov16(1, reg);
	emith_call_c_func(ssp_pm_write);
	hostreg_clear();
}