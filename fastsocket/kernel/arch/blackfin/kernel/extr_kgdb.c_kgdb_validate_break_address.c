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
 int /*<<< orphan*/  ASYNC_BANK0_BASE ; 
 int /*<<< orphan*/  ASYNC_BANK_SIZE ; 
 scalar_t__ BREAK_INSTR_SIZE ; 
 int /*<<< orphan*/  COREB_L1_CODE_START ; 
 int EFAULT ; 
 scalar_t__ IN_MEM (unsigned long,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L1_CODE_LENGTH ; 
 int /*<<< orphan*/  L1_CODE_START ; 
 int /*<<< orphan*/  L2_LENGTH ; 
 int /*<<< orphan*/  L2_START ; 
 scalar_t__ physical_mem_end ; 
 int raw_smp_processor_id () ; 

int kgdb_validate_break_address(unsigned long addr)
{
	int cpu = raw_smp_processor_id();

	if (addr >= 0x1000 && (addr + BREAK_INSTR_SIZE) <= physical_mem_end)
		return 0;
	if (IN_MEM(addr, BREAK_INSTR_SIZE, ASYNC_BANK0_BASE, ASYNC_BANK_SIZE))
		return 0;
	if (cpu == 0 && IN_MEM(addr, BREAK_INSTR_SIZE, L1_CODE_START, L1_CODE_LENGTH))
		return 0;
#ifdef CONFIG_SMP
	else if (cpu == 1 && IN_MEM(addr, BREAK_INSTR_SIZE, COREB_L1_CODE_START, L1_CODE_LENGTH))
		return 0;
#endif
	if (IN_MEM(addr, BREAK_INSTR_SIZE, L2_START, L2_LENGTH))
		return 0;

	return -EFAULT;
}