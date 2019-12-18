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
 int /*<<< orphan*/  InstImm (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PPC_LWZ ; 
 int /*<<< orphan*/  R_OPSTACK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * buf ; 
 size_t compiledOfs ; 
 int /*<<< orphan*/ * opStackIntRegisters ; 
 int /*<<< orphan*/ ** opStackLoadInstructionAddr ; 
 int* opStackRegType ; 

__attribute__((used)) static void loadOpStack(int depth)
{
	// Back off operand stack pointer and reload all operands.
//	InstImm( "addi", PPC_ADDI, R_OPSTACK, R_OPSTACK, -(depth)*4 );

	int i;
	
	for(i = 0; i < depth; i++)
	{
		assert(opStackRegType[i] == 0);
		// For now we're stuck reloading everything as an integer.
		opStackLoadInstructionAddr[i] = &buf[compiledOfs];
		InstImm( "lwz", PPC_LWZ, opStackIntRegisters[i], R_OPSTACK, i*4+4);
		opStackRegType[i] = 1;
	}	
}