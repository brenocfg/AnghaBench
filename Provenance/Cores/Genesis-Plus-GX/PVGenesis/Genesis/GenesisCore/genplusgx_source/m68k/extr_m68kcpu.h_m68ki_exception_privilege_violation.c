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
 scalar_t__* CYC_EXCEPTION ; 
 scalar_t__* CYC_INSTRUCTION ; 
 size_t EXCEPTION_PRIVILEGE_VIOLATION ; 
 int /*<<< orphan*/  INSTRUCTION_NO ; 
 size_t REG_IR ; 
 scalar_t__ REG_PC ; 
 int /*<<< orphan*/  USE_CYCLES (scalar_t__) ; 
 int /*<<< orphan*/  m68ki_init_exception () ; 
 int /*<<< orphan*/  m68ki_jump_vector (size_t) ; 
 int /*<<< orphan*/  m68ki_stack_frame_3word (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m68ki_exception_privilege_violation(void)
{
  uint sr = m68ki_init_exception();

  #if M68K_EMULATE_ADDRESS_ERROR == OPT_ON
  CPU_INSTR_MODE = INSTRUCTION_NO;
  #endif /* M68K_EMULATE_ADDRESS_ERROR */

  m68ki_stack_frame_3word(REG_PC-2, sr);
  m68ki_jump_vector(EXCEPTION_PRIVILEGE_VIOLATION);

  /* Use up some clock cycles and undo the instruction's cycles */
  USE_CYCLES(CYC_EXCEPTION[EXCEPTION_PRIVILEGE_VIOLATION] - CYC_INSTRUCTION[REG_IR]);
}