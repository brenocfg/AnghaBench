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
 scalar_t__ ACC_HI_REG_P (scalar_t__) ; 
 int DImode ; 
 scalar_t__ FP_REG_P (scalar_t__) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_BIG_ENDIAN ; 
 unsigned int UNITS_PER_WORD ; 
 int VOIDmode ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mips_rewrite_small_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_gen_subreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  word_mode ; 

rtx
mips_subword (rtx op, int high_p)
{
  unsigned int byte;
  enum machine_mode mode;

  mode = GET_MODE (op);
  if (mode == VOIDmode)
    mode = DImode;

  if (TARGET_BIG_ENDIAN ? !high_p : high_p)
    byte = UNITS_PER_WORD;
  else
    byte = 0;

  if (REG_P (op))
    {
      if (FP_REG_P (REGNO (op)))
	return gen_rtx_REG (word_mode, high_p ? REGNO (op) + 1 : REGNO (op));
      if (ACC_HI_REG_P (REGNO (op)))
	return gen_rtx_REG (word_mode, high_p ? REGNO (op) : REGNO (op) + 1);
    }

  if (MEM_P (op))
    return mips_rewrite_small_data (adjust_address (op, word_mode, byte));

  return simplify_gen_subreg (word_mode, op, mode, byte);
}