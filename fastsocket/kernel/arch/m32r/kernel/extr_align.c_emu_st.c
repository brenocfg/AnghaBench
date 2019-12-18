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
 unsigned short ISA_STH2 ; 
 int REG1 (unsigned short) ; 
 int REG2 (unsigned short) ; 
 scalar_t__ copy_to_user (unsigned char*,unsigned long*,int) ; 
 unsigned long get_reg (struct pt_regs*,int) ; 
 scalar_t__ insn_check (unsigned long,struct pt_regs*,unsigned char**) ; 
 int /*<<< orphan*/  set_reg (struct pt_regs*,int,unsigned long) ; 

__attribute__((used)) static int emu_st(unsigned long insn32, struct pt_regs *regs)
{
	unsigned char *ucp;
	unsigned long val;
	unsigned short insn16;
	int size, src2;

	insn16 = insn32 >> 16;
	src2 = REG2(insn16);

	ucp = (unsigned char *)get_reg(regs, src2);

	if (insn_check(insn32, regs, &ucp))
		return -1;

	size = insn16 & 0x0040 ? 4 : 2;
	val = get_reg(regs, REG1(insn16));
	if (size == 2)
		val <<= 16;

	/* st inc/dec check */
	if ((insn16 & 0xf0e0) == 0x2060) {
		if (insn16 & 0x0010)
			ucp -= 4;
		else
			ucp += 4;

		set_reg(regs, src2, (unsigned long)ucp);
	}

	if (copy_to_user(ucp, &val, size))
		return -1;

	/* sth inc check */
	if ((insn16 & 0xf0f0) == ISA_STH2) {
		ucp += 2;
		set_reg(regs, src2, (unsigned long)ucp);
	}

	return 0;
}