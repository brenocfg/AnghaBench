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
typedef  int /*<<< orphan*/  uint ;

/* Variables and functions */
 int /*<<< orphan*/  OPER_I_16 () ; 
 scalar_t__ REG_PC ; 
 scalar_t__ REG_PPC ; 
 int /*<<< orphan*/  USE_ALL_CYCLES () ; 
 int /*<<< orphan*/  m68ki_branch_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_trace_t0 () ; 

void m68k_op_bra_16(void)
{
	uint offset = OPER_I_16();
	REG_PC -= 2;
	m68ki_trace_t0();			   /* auto-disable (see m68kcpu.h) */
	m68ki_branch_16(offset);
	if(REG_PC == REG_PPC)
		USE_ALL_CYCLES();
}