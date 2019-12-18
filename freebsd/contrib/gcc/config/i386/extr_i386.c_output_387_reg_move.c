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
 scalar_t__ FIRST_STACK_REG ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_DEAD ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ STACK_TOP_P (int /*<<< orphan*/ ) ; 
 scalar_t__ find_regno_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 char const* output_387_ffreep (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const char *
output_387_reg_move (rtx insn, rtx *operands)
{
  if (REG_P (operands[1])
      && find_regno_note (insn, REG_DEAD, REGNO (operands[1])))
    {
      if (REGNO (operands[0]) == FIRST_STACK_REG)
	return output_387_ffreep (operands, 0);
      return "fstp\t%y0";
    }
  if (STACK_TOP_P (operands[0]))
    return "fld%z1\t%y1";
  return "fst\t%y0";
}