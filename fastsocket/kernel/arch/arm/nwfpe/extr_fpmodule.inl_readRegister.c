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
struct pt_regs {unsigned int* uregs; } ;

/* Variables and functions */
 struct pt_regs* GET_USERREG () ; 
 unsigned int const REG_PC ; 

__attribute__((used)) static inline unsigned long readRegister(const unsigned int nReg)
{
	/* Note: The CPU thinks it has dealt with the current instruction.
	   As a result the program counter has been advanced to the next
	   instruction, and points 4 bytes beyond the actual instruction
	   that caused the invalid instruction trap to occur.  We adjust
	   for this in this routine.  LDF/STF instructions with Rn = PC
	   depend on the PC being correct, as they use PC+8 in their
	   address calculations. */
	struct pt_regs *regs = GET_USERREG();
	unsigned int val = regs->uregs[nReg];
	if (REG_PC == nReg)
		val -= 4;
	return val;
}