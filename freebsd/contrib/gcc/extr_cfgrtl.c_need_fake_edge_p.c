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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ ASM_INPUT ; 
 scalar_t__ ASM_OPERANDS ; 
 scalar_t__ CALL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONST_OR_PURE_CALL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_NORETURN ; 
 int /*<<< orphan*/  SIBLING_CALL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int asm_noperands (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
need_fake_edge_p (rtx insn)
{
  if (!INSN_P (insn))
    return false;

  if ((CALL_P (insn)
       && !SIBLING_CALL_P (insn)
       && !find_reg_note (insn, REG_NORETURN, NULL)
       && !CONST_OR_PURE_CALL_P (insn)))
    return true;

  return ((GET_CODE (PATTERN (insn)) == ASM_OPERANDS
	   && MEM_VOLATILE_P (PATTERN (insn)))
	  || (GET_CODE (PATTERN (insn)) == PARALLEL
	      && asm_noperands (insn) != -1
	      && MEM_VOLATILE_P (XVECEXP (PATTERN (insn), 0, 0)))
	  || GET_CODE (PATTERN (insn)) == ASM_INPUT);
}