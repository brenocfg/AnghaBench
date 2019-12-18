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
struct pt_regs {int dummy; } ;
struct fpustate {int dummy; } ;
typedef  unsigned long s32 ;
typedef  unsigned long s16 ;

/* Variables and functions */
#define  FCMPEQ16_OPF 135 
#define  FCMPEQ32_OPF 134 
#define  FCMPGT16_OPF 133 
#define  FCMPGT32_OPF 132 
#define  FCMPLE16_OPF 131 
#define  FCMPLE32_OPF 130 
#define  FCMPNE16_OPF 129 
#define  FCMPNE32_OPF 128 
 struct fpustate* FPUSTATE ; 
 int /*<<< orphan*/  RD (unsigned int) ; 
 int /*<<< orphan*/  RS1 (unsigned int) ; 
 int /*<<< orphan*/  RS2 (unsigned int) ; 
 unsigned long fpd_regval (struct fpustate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_flush_windows (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_reg (struct pt_regs*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcmp(struct pt_regs *regs, unsigned int insn, unsigned int opf)
{
	struct fpustate *f = FPUSTATE;
	unsigned long rs1, rs2, rd_val, i;

	rs1 = fpd_regval(f, RS1(insn));
	rs2 = fpd_regval(f, RS2(insn));

	rd_val = 0;

	switch (opf) {
	case FCMPGT16_OPF:
		for (i = 0; i < 4; i++) {
			s16 a = (rs1 >> (i * 16)) & 0xffff;
			s16 b = (rs2 >> (i * 16)) & 0xffff;

			if (a > b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPGT32_OPF:
		for (i = 0; i < 2; i++) {
			s32 a = (rs1 >> (i * 32)) & 0xffff;
			s32 b = (rs2 >> (i * 32)) & 0xffff;

			if (a > b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPLE16_OPF:
		for (i = 0; i < 4; i++) {
			s16 a = (rs1 >> (i * 16)) & 0xffff;
			s16 b = (rs2 >> (i * 16)) & 0xffff;

			if (a <= b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPLE32_OPF:
		for (i = 0; i < 2; i++) {
			s32 a = (rs1 >> (i * 32)) & 0xffff;
			s32 b = (rs2 >> (i * 32)) & 0xffff;

			if (a <= b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPNE16_OPF:
		for (i = 0; i < 4; i++) {
			s16 a = (rs1 >> (i * 16)) & 0xffff;
			s16 b = (rs2 >> (i * 16)) & 0xffff;

			if (a != b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPNE32_OPF:
		for (i = 0; i < 2; i++) {
			s32 a = (rs1 >> (i * 32)) & 0xffff;
			s32 b = (rs2 >> (i * 32)) & 0xffff;

			if (a != b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPEQ16_OPF:
		for (i = 0; i < 4; i++) {
			s16 a = (rs1 >> (i * 16)) & 0xffff;
			s16 b = (rs2 >> (i * 16)) & 0xffff;

			if (a == b)
				rd_val |= 1 << i;
		}
		break;

	case FCMPEQ32_OPF:
		for (i = 0; i < 2; i++) {
			s32 a = (rs1 >> (i * 32)) & 0xffff;
			s32 b = (rs2 >> (i * 32)) & 0xffff;

			if (a == b)
				rd_val |= 1 << i;
		}
		break;
	};

	maybe_flush_windows(0, 0, RD(insn), 0);
	store_reg(regs, rd_val, RD(insn));
}