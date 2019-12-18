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
 int CPU_ADDRESS_MASK ; 
 int CPU_SR_MASK ; 
 int /*<<< orphan*/  CPU_TYPE ; 
 int /*<<< orphan*/  CPU_TYPE_000 ; 
 int /*<<< orphan*/  CPU_TYPE_008 ; 
 int /*<<< orphan*/  CPU_TYPE_010 ; 
 int /*<<< orphan*/  CPU_TYPE_020 ; 
 int /*<<< orphan*/  CPU_TYPE_040 ; 
 int /*<<< orphan*/  CPU_TYPE_EC020 ; 
 int CYC_BCC_NOTAKE_B ; 
 int CYC_BCC_NOTAKE_W ; 
 int CYC_DBCC_F_EXP ; 
 int CYC_DBCC_F_NOEXP ; 
 int /*<<< orphan*/  CYC_EXCEPTION ; 
 int /*<<< orphan*/  CYC_INSTRUCTION ; 
 int CYC_MOVEM_L ; 
 int CYC_MOVEM_W ; 
 int CYC_RESET ; 
 int CYC_SCC_R_TRUE ; 
 int CYC_SHIFT ; 
#define  M68K_CPU_TYPE_68000 133 
#define  M68K_CPU_TYPE_68008 132 
#define  M68K_CPU_TYPE_68010 131 
#define  M68K_CPU_TYPE_68020 130 
#define  M68K_CPU_TYPE_68040 129 
#define  M68K_CPU_TYPE_68EC020 128 
 int /*<<< orphan*/ * m68ki_cycles ; 
 int /*<<< orphan*/ * m68ki_exception_cycle_table ; 

void m68k_set_cpu_type(unsigned int cpu_type)
{
	switch(cpu_type)
	{
		case M68K_CPU_TYPE_68000:
			CPU_TYPE         = CPU_TYPE_000;
			CPU_ADDRESS_MASK = 0x00ffffff;
			CPU_SR_MASK      = 0xa71f; /* T1 -- S  -- -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[0];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[0];
			CYC_BCC_NOTAKE_B = -2;
			CYC_BCC_NOTAKE_W = 2;
			CYC_DBCC_F_NOEXP = -2;
			CYC_DBCC_F_EXP   = 2;
			CYC_SCC_R_TRUE   = 2;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 3;
			CYC_SHIFT        = 1;
			CYC_RESET        = 132;
			return;
		case M68K_CPU_TYPE_68008:
			CPU_TYPE         = CPU_TYPE_008;
			CPU_ADDRESS_MASK = 0x003fffff;
			CPU_SR_MASK      = 0xa71f; /* T1 -- S  -- -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[0];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[0];
			CYC_BCC_NOTAKE_B = -2;
			CYC_BCC_NOTAKE_W = 2;
			CYC_DBCC_F_NOEXP = -2;
			CYC_DBCC_F_EXP   = 2;
			CYC_SCC_R_TRUE   = 2;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 3;
			CYC_SHIFT        = 1;
			CYC_RESET        = 132;
			return;
		case M68K_CPU_TYPE_68010:
			CPU_TYPE         = CPU_TYPE_010;
			CPU_ADDRESS_MASK = 0x00ffffff;
			CPU_SR_MASK      = 0xa71f; /* T1 -- S  -- -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[1];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[1];
			CYC_BCC_NOTAKE_B = -4;
			CYC_BCC_NOTAKE_W = 0;
			CYC_DBCC_F_NOEXP = 0;
			CYC_DBCC_F_EXP   = 6;
			CYC_SCC_R_TRUE   = 0;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 3;
			CYC_SHIFT        = 1;
			CYC_RESET        = 130;
			return;
		case M68K_CPU_TYPE_68EC020:
			CPU_TYPE         = CPU_TYPE_EC020;
			CPU_ADDRESS_MASK = 0x00ffffff;
			CPU_SR_MASK      = 0xf71f; /* T1 T0 S  M  -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[2];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[2];
			CYC_BCC_NOTAKE_B = -2;
			CYC_BCC_NOTAKE_W = 0;
			CYC_DBCC_F_NOEXP = 0;
			CYC_DBCC_F_EXP   = 4;
			CYC_SCC_R_TRUE   = 0;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 2;
			CYC_SHIFT        = 0;
			CYC_RESET        = 518;
			return;
		case M68K_CPU_TYPE_68020:
			CPU_TYPE         = CPU_TYPE_020;
			CPU_ADDRESS_MASK = 0xffffffff;
			CPU_SR_MASK      = 0xf71f; /* T1 T0 S  M  -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[2];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[2];
			CYC_BCC_NOTAKE_B = -2;
			CYC_BCC_NOTAKE_W = 0;
			CYC_DBCC_F_NOEXP = 0;
			CYC_DBCC_F_EXP   = 4;
			CYC_SCC_R_TRUE   = 0;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 2;
			CYC_SHIFT        = 0;
			CYC_RESET        = 518;
			return;
		case M68K_CPU_TYPE_68040:		// TODO: these values are not correct
			CPU_TYPE         = CPU_TYPE_040;
			CPU_ADDRESS_MASK = 0xffffffff;
			CPU_SR_MASK      = 0xf71f; /* T1 T0 S  M  -- I2 I1 I0 -- -- -- X  N  Z  V  C  */
			CYC_INSTRUCTION  = m68ki_cycles[2];
			CYC_EXCEPTION    = m68ki_exception_cycle_table[2];
			CYC_BCC_NOTAKE_B = -2;
			CYC_BCC_NOTAKE_W = 0;
			CYC_DBCC_F_NOEXP = 0;
			CYC_DBCC_F_EXP   = 4;
			CYC_SCC_R_TRUE   = 0;
			CYC_MOVEM_W      = 2;
			CYC_MOVEM_L      = 2;
			CYC_SHIFT        = 0;
			CYC_RESET        = 518;
			return;
	}
}