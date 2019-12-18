#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int death; } ;

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_INC ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_regno_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mark_life (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ multiple_sets (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_mark_life (int,int /*<<< orphan*/ ,int,int,int) ; 
 TYPE_1__* qty ; 
 scalar_t__ reg_overlap_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t* reg_qty ; 
 int /*<<< orphan*/  rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_insn ; 
 int this_insn_number ; 

__attribute__((used)) static void
wipe_dead_reg (rtx reg, int output_p)
{
  int regno = REGNO (reg);

  /* If this insn has multiple results,
     and the dead reg is used in one of the results,
     extend its life to after this insn,
     so it won't get allocated together with any other result of this insn.

     It is unsafe to use !single_set here since it will ignore an unused
     output.  Just because an output is unused does not mean the compiler
     can assume the side effect will not occur.   Consider if REG appears
     in the address of an output and we reload the output.  If we allocate
     REG to the same hard register as an unused output we could set the hard
     register before the output reload insn.  */
  if (GET_CODE (PATTERN (this_insn)) == PARALLEL
      && multiple_sets (this_insn))
    {
      int i;
      for (i = XVECLEN (PATTERN (this_insn), 0) - 1; i >= 0; i--)
	{
	  rtx set = XVECEXP (PATTERN (this_insn), 0, i);
	  if (GET_CODE (set) == SET
	      && !REG_P (SET_DEST (set))
	      && !rtx_equal_p (reg, SET_DEST (set))
	      && reg_overlap_mentioned_p (reg, SET_DEST (set)))
	    output_p = 1;
	}
    }

  /* If this register is used in an auto-increment address, then extend its
     life to after this insn, so that it won't get allocated together with
     the result of this insn.  */
  if (! output_p && find_regno_note (this_insn, REG_INC, regno))
    output_p = 1;

  if (regno < FIRST_PSEUDO_REGISTER)
    {
      mark_life (regno, GET_MODE (reg), 0);

      /* If a hard register is dying as an output, mark it as in use at
	 the beginning of this insn (the above statement would cause this
	 not to happen).  */
      if (output_p)
	post_mark_life (regno, GET_MODE (reg), 1,
			2 * this_insn_number, 2 * this_insn_number + 1);
    }

  else if (reg_qty[regno] >= 0)
    qty[reg_qty[regno]].death = 2 * this_insn_number + output_p;
}