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
 int BLKmode ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 unsigned int GET_MODE_SIZE (int) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 unsigned int UNITS_PER_WORD ; 
 int VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjust_address_nv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ reload_completed ; 
 int /*<<< orphan*/  replace_equiv_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_gen_subreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  strict_memory_address_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  word_mode ; 

rtx
operand_subword (rtx op, unsigned int offset, int validate_address, enum machine_mode mode)
{
  if (mode == VOIDmode)
    mode = GET_MODE (op);

  gcc_assert (mode != VOIDmode);

  /* If OP is narrower than a word, fail.  */
  if (mode != BLKmode
      && (GET_MODE_SIZE (mode) < UNITS_PER_WORD))
    return 0;

  /* If we want a word outside OP, return zero.  */
  if (mode != BLKmode
      && (offset + 1) * UNITS_PER_WORD > GET_MODE_SIZE (mode))
    return const0_rtx;

  /* Form a new MEM at the requested address.  */
  if (MEM_P (op))
    {
      rtx new = adjust_address_nv (op, word_mode, offset * UNITS_PER_WORD);

      if (! validate_address)
	return new;

      else if (reload_completed)
	{
	  if (! strict_memory_address_p (word_mode, XEXP (new, 0)))
	    return 0;
	}
      else
	return replace_equiv_address (new, XEXP (new, 0));
    }

  /* Rest can be handled by simplify_subreg.  */
  return simplify_gen_subreg (word_mode, op, mode, (offset * UNITS_PER_WORD));
}