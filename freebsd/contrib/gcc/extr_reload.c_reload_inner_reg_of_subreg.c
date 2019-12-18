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
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 size_t FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (size_t) ; 
 int /*<<< orphan*/  HARD_REGNO_MODE_OK (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PLUS ; 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int UNITS_PER_WORD ; 
 scalar_t__** hard_regno_nregs ; 
 int /*<<< orphan*/  subreg_regno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
reload_inner_reg_of_subreg (rtx x, enum machine_mode mode, int output)
{
  rtx inner;

  /* Only SUBREGs are problematical.  */
  if (GET_CODE (x) != SUBREG)
    return 0;

  inner = SUBREG_REG (x);

  /* If INNER is a constant or PLUS, then INNER must be reloaded.  */
  if (CONSTANT_P (inner) || GET_CODE (inner) == PLUS)
    return 1;

  /* If INNER is not a hard register, then INNER will not need to
     be reloaded.  */
  if (!REG_P (inner)
      || REGNO (inner) >= FIRST_PSEUDO_REGISTER)
    return 0;

  /* If INNER is not ok for MODE, then INNER will need reloading.  */
  if (! HARD_REGNO_MODE_OK (subreg_regno (x), mode))
    return 1;

  /* If the outer part is a word or smaller, INNER larger than a
     word and the number of regs for INNER is not the same as the
     number of words in INNER, then INNER will need reloading.  */
  return (GET_MODE_SIZE (mode) <= UNITS_PER_WORD
	  && output
	  && GET_MODE_SIZE (GET_MODE (inner)) > UNITS_PER_WORD
	  && ((GET_MODE_SIZE (GET_MODE (inner)) / UNITS_PER_WORD)
	      != (int) hard_regno_nregs[REGNO (inner)][GET_MODE (inner)]));
}