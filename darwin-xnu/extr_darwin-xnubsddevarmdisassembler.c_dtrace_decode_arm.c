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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int BITS (int /*<<< orphan*/ ,int,int) ; 
 int FASTTRAP_T_INV ; 
 int arm_branch_link_blockdata (int /*<<< orphan*/ ) ; 
 int arm_dataproc_misc (int /*<<< orphan*/ ) ; 
 int arm_loadstore_wordbyte (int /*<<< orphan*/ ) ; 
 int arm_media (int /*<<< orphan*/ ) ; 
 int arm_syscall_coproc (int /*<<< orphan*/ ) ; 
 int arm_unconditional (int /*<<< orphan*/ ) ; 

int dtrace_decode_arm(uint32_t instr)
{
	int cond = BITS(instr,28,0xF), op1 = BITS(instr,25,0x7), op = BITS(instr,4,0x1);

	if (cond == 0xF)
		return arm_unconditional(instr);

	if ((op1 & 0x6) == 0)
		return arm_dataproc_misc(instr);

	if (op1 == 0x2)
		return arm_loadstore_wordbyte(instr);

	if (op1 == 0x3 && op == 0)
		return arm_loadstore_wordbyte(instr);

	if (op1 == 0x3 && op == 1)
		return arm_media(instr);

	if ((op1 & 0x6) == 0x4)
		return arm_branch_link_blockdata(instr);

	if ((op1 & 0x6) == 0x6)
		return arm_syscall_coproc(instr);

	return FASTTRAP_T_INV;
}