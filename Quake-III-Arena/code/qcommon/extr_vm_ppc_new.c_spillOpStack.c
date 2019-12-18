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
 int /*<<< orphan*/  PPC_STFS ; 
 int /*<<< orphan*/  PPC_STW ; 
 int /*<<< orphan*/  R_OPSTACK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * opStackFloatRegisters ; 
 int /*<<< orphan*/ * opStackIntRegisters ; 
 int* opStackRegType ; 

__attribute__((used)) static void spillOpStack(int depth)
{
	// Store out each register on the operand stack to it's correct location.
	int i;
	
	for(i = 0; i < depth; i++)
	{
		assert(opStackRegType[i]);
		assert(opStackRegType[i] == 1);
		switch(opStackRegType[i])
		{
			case 1:	// Integer register
				InstImm( "stw", PPC_STW, opStackIntRegisters[i], R_OPSTACK, i*4+4);
				break;
			case 2: // Float register
				InstImm( "stfs", PPC_STFS, opStackFloatRegisters[i], R_OPSTACK, i*4+4);
				break;
		}
		opStackRegType[i] = 0;
	}
}