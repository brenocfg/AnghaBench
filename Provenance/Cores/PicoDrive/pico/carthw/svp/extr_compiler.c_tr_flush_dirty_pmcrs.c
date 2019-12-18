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
typedef  int u32 ;
struct TYPE_3__ {int v; } ;
struct TYPE_4__ {int emu_status; int* pmac_read; int* pmac_write; TYPE_1__ pmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_ANOMALY ; 
 int /*<<< orphan*/  EOP_STR_IMM (int,int,int) ; 
 int KRREG_PMC ; 
 int SSP_PMC ; 
 int SSP_PMC_HAVE_ADDR ; 
 int SSP_PMC_SET ; 
 int dirty_regb ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  emith_move_r_imm (int,int) ; 
 int* hostreg_r ; 
 TYPE_2__ known_regs ; 
 int /*<<< orphan*/  tr_unhandled () ; 

__attribute__((used)) static void tr_flush_dirty_pmcrs(void)
{
	u32 i, val = (u32)-1;
	if (!(dirty_regb & 0x3ff80000)) return;

	if (dirty_regb & KRREG_PMC) {
		val = known_regs.pmc.v;
		emith_move_r_imm(1, val);
		EOP_STR_IMM(1,7,0x400+SSP_PMC*4);

		if (known_regs.emu_status & (SSP_PMC_SET|SSP_PMC_HAVE_ADDR)) {
			elprintf(EL_ANOMALY, "!! SSP_PMC_SET|SSP_PMC_HAVE_ADDR set on flush\n");
			tr_unhandled();
		}
	}
	for (i = 0; i < 5; i++)
	{
		if (dirty_regb & (1 << (20+i))) {
			if (val != known_regs.pmac_read[i]) {
				val = known_regs.pmac_read[i];
				emith_move_r_imm(1, val);
			}
			EOP_STR_IMM(1,7,0x454+i*4); // pmac_read
		}
		if (dirty_regb & (1 << (25+i))) {
			if (val != known_regs.pmac_write[i]) {
				val = known_regs.pmac_write[i];
				emith_move_r_imm(1, val);
			}
			EOP_STR_IMM(1,7,0x46c+i*4); // pmac_write
		}
	}
	dirty_regb &= ~0x3ff80000;
	hostreg_r[1] = -1;
}