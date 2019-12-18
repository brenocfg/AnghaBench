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
 int /*<<< orphan*/  CPU_INSTR_MODE ; 
 int /*<<< orphan*/  CPU_RUN_MODE ; 
 scalar_t__ FLAG_S ; 
 int /*<<< orphan*/  INSTRUCTION_YES ; 
 int /*<<< orphan*/  RUN_MODE_NORMAL ; 
 int /*<<< orphan*/  m68ki_exception_privilege_violation () ; 
 int /*<<< orphan*/  m68ki_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m68ki_pull_16 () ; 
 int /*<<< orphan*/  m68ki_pull_32 () ; 
 int /*<<< orphan*/  m68ki_set_sr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m68k_op_rte_32(void)
{
  if(FLAG_S)
  {
    uint new_sr;
    uint new_pc;

    new_sr = m68ki_pull_16();
    new_pc = m68ki_pull_32();
    m68ki_jump(new_pc);
    m68ki_set_sr(new_sr);

#if M68K_EMULATE_ADDRESS_ERROR
    CPU_INSTR_MODE = INSTRUCTION_YES;
    CPU_RUN_MODE = RUN_MODE_NORMAL;
#endif

    return;
  }
  m68ki_exception_privilege_violation();
}