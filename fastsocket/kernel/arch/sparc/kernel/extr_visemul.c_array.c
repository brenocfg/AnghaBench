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

/* Variables and functions */
#define  ARRAY16_OPF 129 
#define  ARRAY32_OPF 128 
 int /*<<< orphan*/  RD (unsigned int) ; 
 int /*<<< orphan*/  RS1 (unsigned int) ; 
 int /*<<< orphan*/  RS2 (unsigned int) ; 
 unsigned long fetch_reg (int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  maybe_flush_windows (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_reg (struct pt_regs*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void array(struct pt_regs *regs, unsigned int insn, unsigned int opf)
{
	unsigned long rs1, rs2, rd_val;
	unsigned int bits, bits_mask;

	maybe_flush_windows(RS1(insn), RS2(insn), RD(insn), 0);
	rs1 = fetch_reg(RS1(insn), regs);
	rs2 = fetch_reg(RS2(insn), regs);

	bits = (rs2 > 5 ? 5 : rs2);
	bits_mask = (1UL << bits) - 1UL;

	rd_val = ((((rs1 >> 11) & 0x3) <<  0) |
		  (((rs1 >> 33) & 0x3) <<  2) |
		  (((rs1 >> 55) & 0x1) <<  4) |
		  (((rs1 >> 13) & 0xf) <<  5) |
		  (((rs1 >> 35) & 0xf) <<  9) |
		  (((rs1 >> 56) & 0xf) << 13) |
		  (((rs1 >> 17) & bits_mask) << 17) |
		  (((rs1 >> 39) & bits_mask) << (17 + bits)) |
		  (((rs1 >> 60) & 0xf)       << (17 + (2*bits))));

	switch (opf) {
	case ARRAY16_OPF:
		rd_val <<= 1;
		break;

	case ARRAY32_OPF:
		rd_val <<= 2;
	};

	store_reg(regs, rd_val, RD(insn));
}