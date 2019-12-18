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
 unsigned short ISA_LD2 ; 
 int REG1 (unsigned short) ; 
 int REG2 (unsigned short) ; 
 scalar_t__ copy_from_user (unsigned long*,unsigned char*,int) ; 
 scalar_t__ get_reg (struct pt_regs*,int) ; 
 scalar_t__ insn_check (unsigned long,struct pt_regs*,unsigned char**) ; 
 int /*<<< orphan*/  set_reg (struct pt_regs*,int,unsigned long) ; 

__attribute__((used)) static int emu_ld(unsigned long insn32, struct pt_regs *regs)
{
	unsigned char *ucp;
	unsigned long val;
	unsigned short insn16;
	int size, src;

	insn16 = insn32 >> 16;
	src = REG2(insn16);
	ucp = (unsigned char *)get_reg(regs, src);

	if (insn_check(insn32, regs, &ucp))
		return -1;

	size = insn16 & 0x0040 ? 4 : 2;
	if (copy_from_user(&val, ucp, size))
		return -1;

	if (size == 2)
		val >>= 16;

	/* ldh sign check */
	if ((insn16 & 0x00f0) == 0x00a0 && (val & 0x8000))
		val |= 0xffff0000;

	set_reg(regs, REG1(insn16), val);

	/* ld increment check */
	if ((insn16 & 0xf0f0) == ISA_LD2)	/* ld Rdest, @Rsrc+ */
		set_reg(regs, src, (unsigned long)(ucp + 4));

	return 0;
}