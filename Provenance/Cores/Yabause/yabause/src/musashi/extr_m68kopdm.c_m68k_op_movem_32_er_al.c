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
typedef  int uint ;

/* Variables and functions */
 int CYC_MOVEM_L ; 
 int EA_AL_32 () ; 
 int OPER_I_16 () ; 
 int /*<<< orphan*/ * REG_DA ; 
 int /*<<< orphan*/  USE_CYCLES (int) ; 
 int /*<<< orphan*/  m68ki_read_32 (int) ; 

void m68k_op_movem_32_er_al(void)
{
	uint i = 0;
	uint register_list = OPER_I_16();
	uint ea = EA_AL_32();
	uint count = 0;

	for(; i < 16; i++)
		if(register_list & (1 << i))
		{
			REG_DA[i] = m68ki_read_32(ea);
			ea += 4;
			count++;
		}

	USE_CYCLES(count<<CYC_MOVEM_L);
}