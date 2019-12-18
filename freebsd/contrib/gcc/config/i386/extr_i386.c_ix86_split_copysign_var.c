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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtx_AND (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_IOR (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_NOT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_gen_subreg (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
ix86_split_copysign_var (rtx operands[])
{
  enum machine_mode mode, vmode;
  rtx dest, scratch, op0, op1, mask, nmask, x;

  dest = operands[0];
  scratch = operands[1];
  op0 = operands[2];
  op1 = operands[3];
  nmask = operands[4];
  mask = operands[5];

  mode = GET_MODE (dest);
  vmode = GET_MODE (mask);

  if (rtx_equal_p (op0, op1))
    {
      /* Shouldn't happen often (it's useless, obviously), but when it does
	 we'd generate incorrect code if we continue below.  */
      emit_move_insn (dest, op0);
      return;
    }

  if (REG_P (mask) && REGNO (dest) == REGNO (mask))	/* alternative 0 */
    {
      gcc_assert (REGNO (op1) == REGNO (scratch));

      x = gen_rtx_AND (vmode, scratch, mask);
      emit_insn (gen_rtx_SET (VOIDmode, scratch, x));

      dest = mask;
      op0 = simplify_gen_subreg (vmode, op0, mode, 0);
      x = gen_rtx_NOT (vmode, dest);
      x = gen_rtx_AND (vmode, x, op0);
      emit_insn (gen_rtx_SET (VOIDmode, dest, x));
    }
  else
    {
      if (REGNO (op1) == REGNO (scratch))		/* alternative 1,3 */
	{
	  x = gen_rtx_AND (vmode, scratch, mask);
	}
      else						/* alternative 2,4 */
	{
          gcc_assert (REGNO (mask) == REGNO (scratch));
          op1 = simplify_gen_subreg (vmode, op1, mode, 0);
	  x = gen_rtx_AND (vmode, scratch, op1);
	}
      emit_insn (gen_rtx_SET (VOIDmode, scratch, x));

      if (REGNO (op0) == REGNO (dest))			/* alternative 1,2 */
	{
	  dest = simplify_gen_subreg (vmode, op0, mode, 0);
	  x = gen_rtx_AND (vmode, dest, nmask);
	}
      else						/* alternative 3,4 */
	{
          gcc_assert (REGNO (nmask) == REGNO (dest));
	  dest = nmask;
	  op0 = simplify_gen_subreg (vmode, op0, mode, 0);
	  x = gen_rtx_AND (vmode, dest, op0);
	}
      emit_insn (gen_rtx_SET (VOIDmode, dest, x));
    }

  x = gen_rtx_IOR (vmode, dest, scratch);
  emit_insn (gen_rtx_SET (VOIDmode, dest, x));
}