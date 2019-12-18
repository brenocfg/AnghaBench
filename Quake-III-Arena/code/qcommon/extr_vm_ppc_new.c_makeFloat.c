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

/* Variables and functions */
 int /*<<< orphan*/  Inst (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InstImm (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int PPC_LFS ; 
 unsigned int PPC_LFSX ; 
 unsigned int PPC_LWZ ; 
 int /*<<< orphan*/  PPC_ORI ; 
 unsigned int PPC_STW ; 
 int /*<<< orphan*/  R_OPSTACK ; 
 int /*<<< orphan*/ * opStackFloatRegisters ; 
 int /*<<< orphan*/ * opStackIntRegisters ; 
 unsigned int** opStackLoadInstructionAddr ; 
 int* opStackRegType ; 

__attribute__((used)) static void makeFloat(int depth)
{
	//assert(opStackRegType[depth] == 1);
	if(opStackRegType[depth] == 1)
	{
		unsigned instruction;
		unsigned destReg, aReg, bReg, imm;
		
		if(opStackLoadInstructionAddr[depth])
		{
			// Repatch load instruction to use LFS instead of LWZ
			instruction = *opStackLoadInstructionAddr[depth];
			// Figure out if it's LWZ or LWZX
			if((instruction & 0xfc000000) == PPC_LWZ)
			{
				//printf("patching LWZ at %p to LFS at depth %ld\n",opStackLoadInstructionAddr[depth],depth);
				//printf("old instruction: %08lx\n",instruction);
				// Extract registers
				destReg = (instruction >> 21) & 31;
				aReg    = (instruction >> 16) & 31;
				imm     = instruction & 0xffff;
				
				// Calculate correct FP register to use.
				// THIS ASSUMES REGISTER USAGE FOR THE STACK IS n, n+1, n+2, etc!
				//printf("old dest: %ld\n",destReg);
				destReg = (destReg - opStackIntRegisters[0]) + opStackFloatRegisters[0];
				instruction = PPC_LFS | ( destReg << 21 ) | ( aReg << 16 ) | imm ;			
				//printf("new dest: %ld\n",destReg);
				//printf("new instruction: %08lx\n",instruction);
			}
			else
			{
				//printf("patching LWZX at %p to LFSX at depth %ld\n",opStackLoadInstructionAddr[depth],depth);
				//printf("old instruction: %08lx\n",instruction);
				// Extract registers
				destReg = (instruction >> 21) & 31;
				aReg    = (instruction >> 16) & 31;
				bReg    = (instruction >> 11) & 31;
				// Calculate correct FP register to use.
				// THIS ASSUMES REGISTER USAGE FOR THE STACK IS n, n+1, n+2, etc!
				//printf("old dest: %ld\n",destReg);
				destReg = (destReg - opStackIntRegisters[0]) + opStackFloatRegisters[0];
				instruction = PPC_LFSX | ( destReg << 21 ) | ( aReg << 16 ) | ( bReg << 11 ) ;			
				//printf("new dest: %ld\n",destReg);
				//printf("new instruction: %08lx\n",instruction);
			}
			*opStackLoadInstructionAddr[depth] = instruction;
			opStackLoadInstructionAddr[depth] = 0;
		}
		else
		{	
			//printf("doing float constant load at %p for depth %ld\n",&buf[compiledOfs],depth);
			// It was likely loaded as a constant so we have to save/load it.  A more
			// interesting implementation might be to generate code to do a "PC relative"
			// load from the VM code region.
			InstImm( "stw", PPC_STW, opStackIntRegisters[depth], R_OPSTACK, depth*4+4);
			// For XXX make sure we force enough NOPs to get the load into
			// another dispatch group to avoid pipeline flush.
			Inst( "ori", PPC_ORI,  0, 0, 0 );
			Inst( "ori", PPC_ORI,  0, 0, 0 );
			Inst( "ori", PPC_ORI,  0, 0, 0 );
			Inst( "ori", PPC_ORI,  0, 0, 0 );
			InstImm( "lfs", PPC_LFS, opStackFloatRegisters[depth], R_OPSTACK, depth*4+4);
		}
		opStackRegType[depth] = 2;
	}
}