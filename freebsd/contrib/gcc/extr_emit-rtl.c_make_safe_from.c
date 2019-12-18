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
 int /*<<< orphan*/  CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
#define  SIGN_EXTEND 131 
#define  STRICT_LOW_PART 130 
#define  SUBREG 129 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  ZERO_EXTEND 128 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 scalar_t__ reg_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rtx
make_safe_from (rtx x, rtx other)
{
  while (1)
    switch (GET_CODE (other))
      {
      case SUBREG:
	other = SUBREG_REG (other);
	break;
      case STRICT_LOW_PART:
      case SIGN_EXTEND:
      case ZERO_EXTEND:
	other = XEXP (other, 0);
	break;
      default:
	goto done;
      }
 done:
  if ((MEM_P (other)
       && ! CONSTANT_P (x)
       && !REG_P (x)
       && GET_CODE (x) != SUBREG)
      || (REG_P (other)
	  && (REGNO (other) < FIRST_PSEUDO_REGISTER
	      || reg_mentioned_p (other, x))))
    {
      rtx temp = gen_reg_rtx (GET_MODE (x));
      emit_move_insn (temp, x);
      return temp;
    }
  return x;
}