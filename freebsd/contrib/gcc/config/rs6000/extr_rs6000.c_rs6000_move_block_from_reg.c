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
 int /*<<< orphan*/  BLKmode ; 
 int DImode ; 
 int GET_MODE_SIZE (int) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int SImode ; 
 scalar_t__ TARGET_32BIT ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjust_address_nv (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,int) ; 
 scalar_t__ reload_completed ; 
 int /*<<< orphan*/  replace_equiv_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_gen_subreg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strict_memory_address_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rs6000_move_block_from_reg (int regno, rtx x, int nregs)
{
  int i;
  enum machine_mode reg_mode = TARGET_32BIT ? SImode : DImode;

  if (nregs == 0)
    return;

  for (i = 0; i < nregs; i++)
    {
      rtx tem = adjust_address_nv (x, reg_mode, i * GET_MODE_SIZE (reg_mode));
      if (reload_completed)
	{
	  if (! strict_memory_address_p (reg_mode, XEXP (tem, 0)))
	    tem = NULL_RTX;
	  else
	    tem = simplify_gen_subreg (reg_mode, x, BLKmode,
				       i * GET_MODE_SIZE (reg_mode));
	}
      else
	tem = replace_equiv_address (tem, XEXP (tem, 0));

      gcc_assert (tem);

      emit_move_insn (tem, gen_rtx_REG (reg_mode, regno + i));
    }
}